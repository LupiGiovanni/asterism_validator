//
// Created by gionimbus on 12/16/25.
//

#include "Board.h"
#include "global_functions.h"

Board::Board (const Board_type type) {
    if (type == Board_type::type1)
    {
        Point A1(-304.000000, 465.000000);
        Point B1(-304.000000, 354.085880);
        Point C1(-186.071797, 286.000000);
        Point D1(-40.000000, 286.000000);
        Point E1(-40.000000, 126.504389);
        Point F1(-20.000000, 99.837722);
        Point G1(20.000000, 99.837722);
        Point H1(40.000000, 126.504389);
        Point I1(40.000000, 286.000000);
        Point J1(185.744919, 286.000000);
        Point K1(219.000000, 305.199830);
        Point L1(219.000000, 465.000000);
        Point M1(0.000000, 134.573504);
        Point N1(-300.000000, 284.573504);
        Point O1(-300.000000, -15.426496);
        Point P1(300.000000, -15.426496);
        Point Q1(300.000000, 284.573504);

        profile.push_back(A1);
        profile.push_back(B1);
        profile.push_back(C1);
        profile.push_back(D1);
        profile.push_back(E1);
        profile.push_back(F1);
        profile.push_back(G1);
        profile.push_back(H1);
        profile.push_back(I1);
        profile.push_back(J1);
        profile.push_back(K1);
        profile.push_back(L1);

        pom = M1;
        pom_home = M1;

        pom_range.push_back(N1);
        pom_range.push_back(O1);
        pom_range.push_back(P1);
        pom_range.push_back(Q1);

        rotate(profile, M_PI / 2.);
        rotate(pom, M_PI / 2.);
        rotate(pom_home, M_PI / 2.);
        rotate(pom_range, M_PI / 2.);
    }
    else if (type == Board_type::type2)
    {
        Point A2(-250.701813, -495.771723);
        Point B2(-154.647367, -440.314663);
        Point C2(-154.647367, -304.142903);
        Point D2(-227.683265, -177.641016);
        Point E2(-89.556015, -97.893211);
        Point F2(-76.462004, -67.239369);
        Point G2(-96.212004, -33.031366);
        Point H2(-129.167880, -28.387089);
        Point I2(-267.683265, -108.358984);
        Point J2(-340.555725, 17.859819);
        Point K2(-373.810806, 37.059649);
        Point L2(-512.201813, -42.840437);
        Point M2(-116.544073, -67.286752);
        Point N2(-96.447884, -402.094373);
        Point O2(163.359737, -252.094373);
        Point P2(-136.640263, 267.520869);
        Point Q2(-396.447884, 117.520869);

        profile.push_back(A2);
        profile.push_back(B2);
        profile.push_back(C2);
        profile.push_back(D2);
        profile.push_back(E2);
        profile.push_back(F2);
        profile.push_back(G2);
        profile.push_back(H2);
        profile.push_back(I2);
        profile.push_back(J2);
        profile.push_back(K2);
        profile.push_back(L2);

        pom = M2;
        pom_home = M2;

        pom_range.push_back(N2);
        pom_range.push_back(O2);
        pom_range.push_back(P2);
        pom_range.push_back(Q2);

        rotate(profile, M_PI / 2.);
        rotate(pom, M_PI / 2.);
        rotate(pom_home, M_PI / 2.);
        rotate(pom_range, M_PI / 2.);
    }
    else if (type == Board_type::type3)
    {
        Point A3(554.701813, 30.771723);
        Point B3(458.647367, 86.228783);
        Point C3(340.719164, 18.142903);
        Point D3(267.683265, -108.358984);
        Point E3(129.556015, -28.611178);
        Point F3(96.462004, -32.598353);
        Point G3(76.462004, -67.239369);
        Point H3(89.556015, -97.893211);
        Point I3(227.683265, -177.641016);
        Point J3(154.810806, -303.859819);
        Point K3(154.810806, -342.259478);
        Point L3(293.201813, -422.159563);
        Point M3(116.544073, -67.286752);
        Point N3(396.447884, 117.520869);
        Point O3(136.640263, 267.520869);
        Point P3(-163.359737, -252.094373);
        Point Q3(96.447884, -402.094373);

        profile.push_back(A3);
        profile.push_back(B3);
        profile.push_back(C3);
        profile.push_back(D3);
        profile.push_back(E3);
        profile.push_back(F3);
        profile.push_back(G3);
        profile.push_back(H3);
        profile.push_back(I3);
        profile.push_back(J3);
        profile.push_back(K3);
        profile.push_back(L3);

        pom = M3;
        pom_home = M3;

        pom_range.push_back(N3);
        pom_range.push_back(O3);
        pom_range.push_back(P3);
        pom_range.push_back(Q3);

        rotate(profile, M_PI / 2.);
        rotate(pom, M_PI / 2.);
        rotate(pom_home, M_PI / 2.);
        rotate(pom_range, M_PI / 2.);
    }
}

bool Board::is_in_range (const Point& point) const {
    if (pom_range.bounded_side(point) == CGAL::ON_BOUNDED_SIDE || pom_range.bounded_side(point) == CGAL::ON_BOUNDARY)
        return true;
    return false;
}

bool Board::teleport (double delta_x, double delta_y) {
    Vector displacement (delta_x, delta_y);
    Point destination = pom + displacement;

    if (!is_in_range(destination))
        return false;

    for (auto it = profile.begin(); it != profile.end(); ++it)
        *it = *it + displacement;

    pom = destination;

    return true;
}

bool Board::teleport (const Point& pom_destination) {
    return teleport (pom_destination.x() - pom.x(), pom_destination.y() - pom.y());
}

void Board::move_step_linear (const Point& pom_destination, const double step_mm) {
    Vector displacement (pom_destination - pom);
    double length = std::sqrt(displacement.squared_length());
    Vector step_vector = (displacement / length) * step_mm;

    teleport (pom + step_vector);

    //TODO: implement control for when destination is reached
}

