double alpha(double q2) { // alpha_s(Q^2): Running Coupling Constant [10]pg.5
        double pi = 3.141592653589793238,
                nf, lambda, b0, b1, psi, b2, b3;

	// *** define nf globally
        // lambda2
        double lambda2, mu2, ln;
        nf = 3.0; // N_f: number of quark flavors ("N_f being the number of active flavors") [8]pg.13
        lambda = 0.3; // lambda_n: [8]pg.13
        //mu = 91.1876; //Z boson mass
        mu2 = q2; // mu^2 = 10 (GeV/c)^2 (Reference Scale) [8]pg.13
        lambda2 = lambda*lambda;
        psi = 1.20206; // Apery const
        b0 = 11.0 - 2.0*nf/3.0; // [10]pg.5
        b1 = 102.0 - (38.0*nf) / 3.0; // [10]pg.5
        b2 = 2857.0 / 2.0 - 5033.0 / 18.0*nf + 325.0 / 54.0*nf*nf;
        b3 = (149753.0 / 6.0 + 3564.0*psi) - (1078361.0 / 162.0 + 6508.0 / 27.0*psi)*nf +
                (50065.0 / 162.0 + 6475.0 / 81.0 * psi)*nf*nf + 1093.0 / 729.0*nf*nf*nf;
        ln = log(mu2 / lambda2); // L: [10]pg.5

        //return 4.0*pi / (b0*ln) * (1.0 - b1 / (b0*b0) * log(ln) / ln);
        return 4.0*pi / (b0*ln) * (1.0 - b1 / (b0*b0) * log(ln) / ln) + b1*b1 / (pow(b0, 4) * ln) *
                (pow(log(ln), 2) - log(ln) - 1.0 + b2*b0/(b1*b1)) + pow(b1, 3)/(pow(b0, 6) * pow(ln, 3)) *
                (- pow(log(ln), 3) + 5.0/2.0 * pow(log(ln), 2) + 2.0 * log(ln) - 1.0/2.0 - 3.0*b2*b0 / (b1*b1) *
                log(ln) + b3*(b0*b0) / (2.0 * pow(b1, 3))); // check parenth
}
