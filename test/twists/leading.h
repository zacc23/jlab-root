const double n = 4.0; // "The presence of two distinct higher twist terms for n ≥ 4 is motivated by the
		      //  Q2-behaviour of the total higher twist contribution in the moments" [8]pg.13

double s1(double n) { // [9]pg.23
        // -> gammaE + polygamma(n + 1);
        // summation of 1/j
        double sum = 0;
        for (int j=1; j<=n; j++) {
                sum += 1.0/j;
        }
        return sum;
}

double s2(double n) { // [9]pg.23
        double sum = 0;
        for (int j=1; j<=n; j++) {
                sum += 1.0/(j*j);
        }
        return sum;
}

double sp2(double n) { // sp2: l=2, s'_2 (prime) [9]pg.23
        double sum, l;
        sum = 0;
        l = 2.0;
        
	for (int j=1; j<=n; j++)
        {
                sum += pow(2.0, l - 1.0) * (1.0 + pow(-1.0, j))/pow(j, l);
        }
        return sum;
}

double sp3(double n) { // sp3: l=3, s'_3 (prime) [9]pg.23
        double sum, l;
        sum = 0;
        l = 3.0;

        for (int j=1; j<=n; j++)
        {
                sum += pow(2.0, l - 1.0) * (1.0 + pow(-1.0, j))/pow(j, l);
        }
        return sum;
}

double st(double n) { // st: s (tilde) [9]pg.23
        double sum = 0;

        for (int j=1; j<=n; j++)
        {
                sum += pow(-1.0, j)/(j*j) * s1(j);
        }
        return sum;
}

double leading(double q2) { // leading twist: eta_n(Q^2) [8]pg.13
        double an, mu2, pi = 3.141592653589793238, e = 2.7182818284590452354,
                cn, cdis, cnlog, g1, g2, gn, tf, rn, k, b0, b1, cf, ca, nc, nf,
                gammaE, gammaN, gammaN0, gammaN1, eta, lambdaN;
        mu2 = 10.0; // mu^2 = 10 (GeV/c)^2 (Reference Scale) [8]pg.13
        nf = 3.0; // N_f: number of quark flavors ("N_f being the number of active flavors") [8]pg.13
        tf = nf / 2.0; // [9]pg.21
        b0 = 11.0 - 2.0*nf/3.0;
        b1 = 102.0 - (38.0*nf) / 3.0;

        //an = 1.215E-2; // m_4: eta_4(mu^2) = A_4 = (1.215±0.03±0.01)×10−2 (n = 4); A_n: twist-2 parameter [8]pg.17
	an = 2.95E-3; // m_6
        //an = 1.05E-3; // m_8
        nc = 3.0; // C_A = N_c -> 3 (substitute for C_A) [1]pg.4
        ca = nc; // C_A: [1]pg.4
        cf = (nc*nc - 1.0) / (2.0*nc); // [8]pg.13 (C_F -> 4/3 [1]pg.3)
        k = nc * (67.0 / 18.0 - pi * pi/6.0) - 5.0*nf/9.0; // K: [8]pg.13
        lambdaN = b0 * alpha(q2) * log(n) / (4.0*pi); // lambda_n: [8]pg.13

        gammaE = 0.5772156649015328606065; // Euler-Mascheroni constant [7] (equivalent to TMath::EulerGamma())
        g1 = cf * 4.0/(b0 * lambdaN) * (lambdaN + (1.0 - lambdaN)*log(1.0 - lambdaN)); // G_1(lambda_n): [8]pg.13
        g2 = -cf * (4.0 * gammaE + 3.0)/b0 * log(1.0 - lambdaN)
             -cf * (8.0*k/(b0*b0)) * (lambdaN + log(1.0 - lambdaN))
             +cf * (4.0*b1/pow(b0, 3)) * (lambdaN + log(1.0 - lambdaN) + .5*pow(log(1.0 - lambdaN), 2.0)); // // G_2(lambda_n): "divergent for lambda -> 1" [8]pg.13
        gn = log(n) * g1 + g2; // (without O) G_n: "key quantity of the soft gluon resummation" [8]pg.13
        eta = pow(-1.0, n); // [9]pg.25
        gammaN0 = 2.0 * cf * (4.0 * s1(n) - 3.0 - 2.0/(n * (n - 1.0)) - 4.0 / ((n+1.0)*(n+2.0))) + 8.0/3.0 * tf ; // gamma_0,n: anomalous dimensions [9]pg.21
        gammaN1 = cf*cf * (16.0 * s1(n) * (2.0*n + 1.0) / (n*n * pow(n + 1.0, 2)) + 16.0*(2.0*s1(n) - 1.0/(n*(n+1.0))) *
                  (s2(n) - sp2(n/2.0)) + 24.0*s2(n) + 64.0*st(n) - 8.0*sp3(n/2.0) - 3.0 - 8.0 * (3*(n*n*n) + n*n - 1.0) /
                  (n*n*n * pow(n + 1.0, 3.0)) - 16.0*eta * (2.0*(n*n) + 2.0*n + 1.0) / ((n*n*n) * pow(n + 1.0, 3))) +
                  ca*cf * (536.0/9.0 * s1(n) - 8.0*(2.0*s1(n) - 1/(n*(n + 1.0))) * (2.0*s2(n) - sp2(n/2)) -
                  88.0/3.0 * s2(n) - 32.0*st(n) + 4.0*sp3(n/2) - 17.0/3.0 - 4.0/9.0 *
                  (151.0*n*n*n*n + 236.0*n*n*n + 88.0*n*n + 3.0*n + 18.0)/(n*n*n * pow(n + 1.0, 3.0) +
                  8.0*eta * (2.0*n*n + 2*n + 1.0)/(n*n*n * pow(n + 1.0, 3)))) + cf*tf *
                  (-160.0/9.0 * s1(n) + 32.0/3.0 * s2(n) + 4.0/3.0 + 16.0/9.0 * (11.0*n*n + 5.0*n - 3.0) /
                  (n*n * pow(n + 1.0, 2))); // gamma_1,n: [9]pg.21,22
        gammaN = alpha(q2)/(4.0*pi) * gammaN0 + pow(alpha(q2)/(4.0*pi), 2) * gammaN1; // gamma_n: anomalous dimensions [9]pg.21
        cdis = cf * (gammaE*gammaE + (3.0/2.0)*gammaE - 9.0/2.0 - pi*pi/6.0); // C_DIS^(NLO): [1]pg.3
        cnlog = cf * log(n) * (log(n) + 2.0*gammaE + 3.0/2.0); // C_n,LOG^(NLO): [1]pg.3
        cn = cdis + cnlog; // (without O(1/n)) C_n^(NLO): "NLO part of the quark coefficient function" [1]pg.3
        //rn = (1.0 + alpha(q2)/(2.0*pi) * cdis) * pow(e, gn) + alpha(q2)/(2.0*pi) * (cn - cdis - cnlog) /
        //     (1.0 + alpha(q2)/(2.0*pi) * cn); // r_n(Q^2): "ratio of the quark coefficient function" [1]pg.4
        rn = 2.0 * (cn - cdis - cnlog) + gammaN1 - b1*gammaN/b0; // R_n^NS: [1]pg.3

        return an * pow(alpha(q2) / alpha(mu2), gammaN) *
               ((1.0 + alpha(q2) / (2*pi) * cdis) * pow(e, gn) +
               alpha(q2)/(4.0*pi) * rn);
}
