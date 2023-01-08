#include "PNPair.h"

Point interPoint(PNPair pr1, PNPair pr2)
{
    Point ip;
    Point p1 = pr1.first, p2 = pr2.first;
    UnitVector uv1 = pr1.second, uv2 = pr2.second;
    double tan1 = tan(uv1.theta), tan2 = tan(uv2.theta);
    double x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;

    if (uv1.theta == pi / 2 || uv1.theta == 3 * pi / 2)
    {
        return Point(x1, tan(uv2.theta) * (x2 - x1) + y2);
    }
    if (uv2.theta == pi / 2 || uv2.theta == 3 * pi / 2)
    {
        return Point(x2, tan(uv1.theta) * (x1 - x2) + y1);
    }
    ip.x = (x1 * tan1 - x2 * tan2 + y2 - y1) / (tan1 - tan2);
    ip.y = ((x1 - x2) * tan1 * tan2 + y2 * tan1 - y1 * tan2) / (tan1 - tan2);
    return ip;
}

int isOnSameSide(PNPair pr1, PNPair pr2)
{
    Point p1 = pr1.first, p2 = pr2.first;
    UnitVector uv1 = pr1.second, uv2 = pr2.second;
    Vector v(p1, p2);
    return orientation(v, uv1) * orientation(v, uv2);
}

int isOnSameSide(Point p1, Point p2, Point cp1, Point cp2)
{
    Vector v1(p1, cp1), v2(p2, cp2);
    UnitVector uv1(v1), uv2(v2);
    PNPair pr1(p1, uv1), pr2(p2, uv2);
    return isOnSameSide(pr1, pr2);
}

PNPair newPair(PNPair pr1, PNPair pr2, double omega)
{
    Point p1 = pr1.first, p2 = pr2.first;
    UnitVector uv1 = pr1.second, uv2 = pr2.second;

    double theta = angle(uv1, uv2); //法向的夹角
    if (theta == 0)
        return PNPair((1 - omega) * p1 + omega * p2, uv1);

    double d = distance(p1, p2); //线段的长度
    if (d == 0)
        return PNPair(p1, UnitVector((1 - omega) * uv1.theta + omega * uv2.theta));

    double r = 0.5 * d / sin(theta / 2); //候选弧对应的圆的半径
    Point mp = midPoint(p1, p2); //中点
    double c = 0.5 * sqrt(4 * (r / d) * (r / d) - 1);
    Point p(p2.y - p1.y, p1.x - p2.x);
    Point o1 = mp - c * p, o2 = mp + c * p; //两个候选弧的圆心
    Point ip = interPoint(pr1, pr2);
    Point o; //选中的圆弧的圆心

    if (isOnSameSide(pr1, pr2) < 0)
    {
        // 此时法向异侧，所以选取和交点在相同半平面内的圆弧，也就是圆心和交点在不同半平面内
        if (isOnSameSide(p1, p2, ip, o1) > 0)
        {
            o = o2;
        }
        else
        {
            o = o1;
        }
    }
    else
    {
        // 此时法向同侧，所以选取和交点在不同半平面内的圆弧，也就是圆心和交点在同一半平面内
        if (isOnSameSide(p1, p2, ip, o1) > 0)
        {
            o = o1;
        }
        else
        {
            o = o2;
        }
    }

    double phi = angle(Vector(1.0, 0.0), p1 - o);
    if (orientation(Vector(1.0, 0.0), p1 - o) < 0)
        phi = 2 * pi - phi;
    int flag = orientation(Vector(p2 - p1), Vector(o - p1));

    Point np(o.x + r * cos(phi + flag * omega * theta), o.y + r * sin(phi + flag * omega * theta));
    //Vector n = (1 - omega) * uv1 + omega * uv2;
    //n.normalize();
    UnitVector n((1 - omega) * uv1 + omega * uv2);

    return PNPair(np, n);
}

SubCurve Read()
{
    int n; //输入n对点法向
    SubCurve head = new Node;
    head->Next = nullptr;

    cin >> n;
    PtrToNode last = head;
    PtrToNode temp;
    //PtrToNode tail = nullptr;
    for (int i = 0; i < n; ++i)
    {
        double x, y, alpha;
        cin >> x >> y >> alpha;
        temp = new Node;
        temp->p.first = Point(x, y);
        temp->p.second = UnitVector(alpha);
        temp->Next = nullptr;
        //if (i == 0)
        //{
        //    tail = temp;
        //}
        //if (i != n - 1)
        //{
        //    last->Next = temp;
        //    last = last->Next;
        //}
        //else
        //{
        //    last->Next = temp;
        //    last = last->Next;
        //    last->Next = tail;
        //}
        last->Next = temp;
        last = last->Next;
    }

    return head;
}

void Print(SubCurve c)
{
    PtrToNode temp = c->Next;
    while (temp != nullptr)
    {
        cout << temp->p.first << " " << temp->p.second << endl;
        temp = temp->Next;
    }
}

void printPoint(SubCurve c)
{
    PtrToNode temp = c->Next;
    while (temp != nullptr)
    {
        cout << temp->p.first.x << " " << temp->p.first.y << endl;
        temp = temp->Next;
        // cout << temp->p.first << endl;
    }
}

void addNewPair(SubCurve c)
{
    PtrToNode p0 = c->Next;
    if (p0 == nullptr)  return;
    PtrToNode p1 = p0->Next;
    if (p1 == nullptr)  return;
    PtrToNode pOmega;
    while (p1 != nullptr)
    {
        pOmega = new Node;
        pOmega->p = newPair(p0->p, p1->p, 0.5);
        p0->Next = pOmega;
        pOmega->Next = p1;
        p0 = p1;
        p1 = p1->Next;
    }
}

SubCurve MLR(SubCurve c, int m)
{
    return c;
}

//void M4Pt(SubCurve c)
//{
//    PtrToNode p0 = c->Next;
//    if (p0 == nullptr)  return;
//    PtrToNode p1 = p0->Next;
//    if (p1 == nullptr)  return;
//    PtrToNode p2 = p1->Next;
//    if (p2 == nullptr)  return;
//    PtrToNode p3 = p2->Next;
//    if (p3 == nullptr)  return;
//    PtrToNode SL, SR, newP;
//    while (p3 != nullptr)
//    {
//        SL = new Node;
//        SR = new Node;
//        newP = new Node;
//        SL->p = newPair(p0->p, p1->p, -0.125);
//        SR->p = newPair(p2->p, p3->p, -0.125);
//        newP->p = newPair(SL->p, SR->p, 0.5);
//        newP->Next = p1;
//        p0->Next = newP;
//        p0 = p1;
//        p1 = p1->Next;
//        p2 = p2->Next;
//        p3 = p3->Next;
//    }
//}

vector<PNPair> M4Pt(vector<PNPair>& c, int numSteps)
{
    int inputSize = c.size();
    vector<vector<PNPair> > newPairs(numSteps + 1, vector<PNPair>(inputSize * (int)pow(2, numSteps)));

    for (int i = 0; i < inputSize; ++i)
    {
        newPairs[0][i] = c[i];
    }
    newPairs[0][inputSize] = c[0];
    newPairs[0][inputSize + 1] = c[1];
    newPairs[0][inputSize + 2] = c[2];

    PNPair SL, SR;
    for (int j = 1; j <= numSteps; ++j)
    {
        int lastSize = inputSize * (int)pow(2, j - 1);
        for (int i = 0; i < lastSize; ++i)
        {
            newPairs[j][2 * i] = newPairs[j - 1][i];
            if (i == 0)
            {
                SL = newPair(newPairs[j - 1][i], newPairs[j - 1][lastSize - 1], -0.125);
            }
            else
            {
                SL = newPair(newPairs[j - 1][i], newPairs[j - 1][i - 1], -0.125);
            }
            SR = newPair(newPairs[j - 1][i + 1], newPairs[j - 1][i + 2], -0.125);
            newPairs[j][2 * i + 1] = newPair(SL, SR, 0.5);
        }
        if (j != numSteps)
        {
            newPairs[j][2 * lastSize] = newPairs[j][0];
            newPairs[j][2 * lastSize + 1] = newPairs[j][1];
            newPairs[j][2 * lastSize + 2] = newPairs[j][2];
        }
    }
    //auto first = newPairs[numSteps].begin();
    //auto last = newPairs[numSteps].begin() + inputSize * (int)pow(2, numSteps);
    //vector<PNPair> ret(first, last);
    //return ret;
    return newPairs[numSteps];
}

vector<Point> L4Pt(vector<Point>& p, int numSteps)
{
    int inputSize = p.size();
    vector<vector<Point> > newPoints(numSteps + 1, vector<Point>(inputSize * (int)pow(2, numSteps)));

    for (int i = 0; i < inputSize; ++i)
    {
        newPoints[0][i] = p[i];
    }
    newPoints[0][inputSize] = p[0];
    newPoints[0][inputSize + 1] = p[1];
    newPoints[0][inputSize + 2] = p[2];

    for (int j = 1; j <= numSteps; ++j)
    {
        int lastSize = inputSize * (int)pow(2, j - 1);
        for (int i = 0; i < lastSize; ++i)
        {
            newPoints[j][2 * i] = newPoints[j - 1][i];
            if (i == 0)
            {
                newPoints[j][2 * i + 1] = -1.0 / 16 * (newPoints[j - 1][lastSize - 1] + newPoints[j - 1][i + 2])
                                        + 9.0 / 16 * (newPoints[j - 1][i] + newPoints[j - 1][i + 1]);
            }
            else
            {
                newPoints[j][2 * i + 1] = -1.0 / 16 * (newPoints[j - 1][i - 1] + newPoints[j - 1][i + 2])
                                        + 9.0 / 16 * (newPoints[j - 1][i] + newPoints[j - 1][i + 1]);
            }
        }
        if (j != numSteps)
        {
            newPoints[j][2 * lastSize] = newPoints[j][0];
            newPoints[j][2 * lastSize + 1] = newPoints[j][1];
            newPoints[j][2 * lastSize + 2] = newPoints[j][2];
        }
    }

    return newPoints[numSteps];
}

vector<PNPair> MCC(vector<PNPair>& c, int numSteps)
{
    int inputSize = c.size();
    vector<vector<PNPair> > newPairs(numSteps + 1, vector<PNPair>(inputSize * (int)pow(2, numSteps)));

    for (int i = 0; i < inputSize; ++i)
    {
        newPairs[0][i] = c[i];
    }
    newPairs[0][inputSize] = c[0];

    for (int j = 1; j <= numSteps; ++j)
    {
        int lastSize = inputSize * (int)pow(2, j - 1);
        for (int i = 0; i < lastSize; ++i)
        {
            newPairs[j][2 * i] = newPair(newPairs[j - 1][i], newPairs[j - 1][i + 1], 0.25);
            newPairs[j][2 * i + 1] = newPair(newPairs[j - 1][i], newPairs[j - 1][i + 1], 0.75);
        }
        if (j != numSteps)
        {
            newPairs[j][2 * lastSize] = newPairs[j][0];
        }
    }

    return newPairs[numSteps];
}

vector<Point> Chaikin(vector<Point>& p, int numSteps)
{
    int inputSize = p.size();
    vector<vector<Point> > newPoints(numSteps + 1, vector<Point>(inputSize * (int)pow(2, numSteps)));

    for (int i = 0; i < inputSize; ++i)
    {
        newPoints[0][i] = p[i];
    }
    newPoints[0][inputSize] = p[0];

    for (int j = 1; j <= numSteps; ++j)
    {
        int lastSize = inputSize * (int)pow(2, j - 1);
        for (int i = 0; i < lastSize; ++i)
        {
            newPoints[j][2 * i] = 3.0 / 4 * newPoints[j - 1][i] + 1.0 / 4 * newPoints[j - 1][i + 1];
            newPoints[j][2 * i + 1] = 1.0 / 4 * newPoints[j - 1][i] + 3.0 / 4 * newPoints[j - 1][i + 1];
        }
        if (j != numSteps)
        {
            newPoints[j][2 * lastSize] = newPoints[j][0];
        }
    }

    return newPoints[numSteps];
}

vector<Point> Zigzag(vector<Point>& p1, vector<Point>& p2)
{
    if (p1.size() != p2.size())
    {
        cout << "Error in zigzag!" << endl;
        return p1;
    }

    int outputSize = p1.size() * 2;
    vector<Point> newPoints(outputSize);

    for (int i = 0; i < outputSize; ++i)
    {
        if (i % 2 == 0)
        {
            newPoints[i] = p1[i / 2];
        }
        else
        {
            newPoints[i] = p2[i / 2];
        }
    }

    return newPoints;
}

vector<Point> SF(vector<Point>& p)
{
    int inputSize = p.size();
    vector<Point> pCopy = p;
    vector<Point> newPoints(inputSize);
    pCopy.resize(inputSize + 2);
    pCopy[inputSize] = pCopy[0];
    pCopy[inputSize + 1] = pCopy[1];

    for (int i = 0; i < inputSize; ++i)
    {
        double s, a, b, xx, yy;
        Point temp;
        Vector v1, v2, v3, v4;
        if (i == 0)
        {
            v1 = Vector(pCopy[i + 1] - pCopy[inputSize - 1]);
            v2 = Vector(pCopy[i] - pCopy[inputSize - 1]);
            v3 = Vector(pCopy[i + 1] - pCopy[i + 2]);
            v4 = Vector(pCopy[i] - pCopy[i + 2]);
        }
        else
        {
            v1 = Vector(pCopy[i + 1] - pCopy[i - 1]);
            v2 = Vector(pCopy[i] - pCopy[i - 1]);
            v3 = Vector(pCopy[i + 1] - pCopy[i + 2]);
            v4 = Vector(pCopy[i] - pCopy[i + 2]);
        }
        a = angle(v1, v2) * orientation(v1, v2);
        b = angle(v3, v4) * orientation(v3, v4);
        s = (sin(a) + sin(b)) / 2;
        temp = (pCopy[i + 1] - pCopy[i]) / 2;
        xx = temp.x;
        yy = temp.y;
        temp.setX(-yy);
        temp.setY(xx);
        newPoints[i] = (pCopy[i] + pCopy[i + 1]) / 2 + (s / (1 + sqrt(1 - s * s))) * temp;
    }

    return newPoints;
}

vector<Point> oneStepInGLR(vector<Point>& p, int k)
{
    if (k == 0)
    {
        vector<Point> temp = SF(p);
        return Zigzag(p, temp);
    }
    int inputSize = p.size();
    vector<vector<Point> > newPoints(k + 1, vector<Point>(inputSize * 2));
    vector<Point> temp = SF(p);

    newPoints[0] = Zigzag(p, temp);
    for (int i = 1; i < k + 1; ++i)
    {
        newPoints[i] = SF(newPoints[i - 1]);
    }

    return newPoints[k];
}


vector<Point> GLR(vector<Point>& p, int numSteps, int k)
{
    int inputSize = p.size();
    vector<vector<Point> > newPoints(numSteps + 1, vector<Point>(inputSize * (int)pow(2, numSteps)));
    newPoints[0] = p;
    for (int i = 1; i <= numSteps; ++i)
    {
        newPoints[i] = oneStepInGLR(newPoints[i - 1], k);
    }
    return newPoints[numSteps];
}