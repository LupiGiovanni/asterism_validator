//
// Created by gionimbus on 12/16/25.
//

#include "Board.h"

Board::Board (const Board_type type) {
    if (type == Board_type::type_1) {
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
        Point N1(-305.000000, 287.073504);
        Point O1(-305.000000, -17.926496);
        Point P1(305.000000, -17.926496);
        Point Q1(305.000000, 287.073504);

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

        pom_centre = M1;
        starting_pom_centre = M1;

        pom_range.push_back(N1);
        pom_range.push_back(O1);
        pom_range.push_back(P1);
        pom_range.push_back(Q1);
    }
    else if (type == Board_type::type_2) {
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
        Point N2(-96.112947, -407.674500);
        Point O2(168.024801, -255.174500);
        Point P2(-136.975199, 273.100996);
        Point Q2(-401.112947, 120.600996);

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

        pom_centre = M2;
        starting_pom_centre = M2;

        pom_range.push_back(N2);
        pom_range.push_back(O2);
        pom_range.push_back(P2);
        pom_range.push_back(Q2);
    }
    else if (type == Board_type::type_3) {
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
        Point N3(401.112947, 120.600996);
        Point O3(136.975199, 273.100996);
        Point P3(-168.024801, -255.174500);
        Point Q3(96.112947, -407.674500);

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

        pom_centre = M3;
        starting_pom_centre = M3;

        pom_range.push_back(N3);
        pom_range.push_back(O3);
        pom_range.push_back(P3);
        pom_range.push_back(Q3);
    }
}

bool Board::is_in_range (const Point& point) const {
    if (pom_range.bounded_side(point) == CGAL::ON_BOUNDED_SIDE
        || pom_range.bounded_side(point) == CGAL::ON_BOUNDARY)
        return true;
    return false;
}

bool Board::move (double delta_x, double delta_y) {
    Vector displacement (delta_x, delta_y);
    Point destination = pom_centre + displacement;

    if (!is_in_range(destination))
        return false;

    for (auto it = profile.begin(); it != profile.end(); ++it)
        *it = *it + displacement;

    pom_centre = destination;

    return true;
}

bool Board::move_to_ngs (const Point& ngs) {
    return move(ngs.x() - pom_centre.x(), ngs.y() - pom_centre.y());
}

void Board::reset_to_starting_position() {
    move(starting_pom_centre.x() - pom_centre.x(), starting_pom_centre.y() - pom_centre.y());
}

