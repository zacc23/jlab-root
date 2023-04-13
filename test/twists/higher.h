double higher2(double q2) { // higher twist: HT_2(Q^2) [8]pg.13
        // example of M2 (no error consideration yet):
        double an4, mu2, gammaN4;
        an4 = 4.0 * pow(10.0, -4);
        gammaN4 = 3.4;
        mu2 = 10.0; // mu^2 = 10 (GeV/c)^2 (Reference Scale) [8]pg.13
        return an4 * pow(alpha(q2) / alpha(mu2), gammaN4) * (mu2 / q2);
}

double tw4(double q2) { // higher twist: HT_4(Q^2) [8]pg.13
        // example of M4 (no error consideration yet):
        double an4, an6, mu2, mu4, q4,
                gammaN4, gammaN6;
        //an4 = 7.4E-3;
        an4 = 1.7E-3;
        gammaN4 = 3.0;
        mu2 = 5.0; // mu^2 = 10 (GeV/c)^2 (Reference Scale) [8]pg.13
        mu4 = mu2*mu2;
        q4 = q2*q2;

        // error (from m8_q2.C)
        //Q2err[i] = 0;
        //HTerr[i] = sqrt(pow(HTerr1[i], 2) + pow(HTerr2[i], 2));

        //cout << an4 << " * " << pow(alpha(q2) / alpha(mu2), gammaN4) << " * " << (mu2 / q2) << " + ";
        return an4 * pow(alpha(q2) / alpha(mu2), gammaN4) * mu2 / q2;
}

double tw6(double q2) { // higher twist: HT_4(Q^2) [8]pg.13
        // example of M4 (no error consideration yet):
        double an6, mu2, mu4, q4,
                gammaN4, gammaN6;
        //an6 = -1.5E-2; // M_4
        an6 = -6.6E-3; // M_8
        gammaN6 = 1.9;
        mu2 = 5.0; // mu^2 = 10 (GeV/c)^2 (Reference Scale) [8]pg.13
        mu4 = mu2*mu2;
        q4 = q2*q2;

        // error (from m8_q2.C)
        //Q2err[i] = 0;
        //HTerr[i] = sqrt(pow(HTerr1[i], 2) + pow(HTerr2[i], 2));

        //cout << an6 << " * " << pow(alpha(q2) / alpha(mu2), gammaN6) << " * " << (mu4 / q4) << " = ";
        return  an6 * pow(alpha(q2) / alpha(mu2), gammaN6) * mu4 / q4;
}

double higher(double q2) { // higher twist: HT_4(Q^2) [8]pg.13
        // example of M4 (no error consideration yet):
        //cout << tw4(q2) << " + " << tw6(q2) << " = ";
        return tw4(q2) + tw6(q2);
}

double higher6(double q2) { // higher twist: HT_6(Q^2) [8]pg.13
        // example of M6 (no error consideration yet):
        double an4, an6, mu2, mu4, q4,
                gammaN4, gammaN6;
        an4 = 2.7 * pow(10.0, -3);
        an6 = -9.2 * pow(10.0, -3);
        gammaN4 = 5.9;
        gammaN6 = 4.3;
        mu2 = 10.0; // mu^2 = 10 (GeV/c)^2 (Reference Scale) [8]pg.13
        mu4 = mu2*mu2;
        q4 = q2*q2;
        return an4 * pow(alpha(q2) / alpha(mu2), gammaN4) * (mu2 / q2) +
               an6 * pow(alpha(q2) / alpha(mu2), gammaN6) * (mu4 / q4);
}

double higher8(double q2) { // higher twist: HT_8(Q^2) [8]pg.13
        // example of M8 (no error consideration yet):
        double an4 = .0017, an6 = -.0066,
               mu2, gammaN4 = 6.4, gammaN6 = 4.7;
        mu2 = 10.0; // mu^2 = 10 (GeV/c)^2 (Reference Scale) [8]pg.13
        return an4 * pow(alpha(q2) / alpha(mu2), gammaN4) * (mu2 / q2) +
               an6 * pow(alpha(q2) / alpha(mu2), gammaN6) * (mu2*mu2 / (q2*q2));
}
