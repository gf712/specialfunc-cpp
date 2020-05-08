/*
 * This software is distributed under BSD 3-clause license (see LICENSE file).
 *
 * Authors: Gil Hoben
 */

extern "C" {
    #include "zbsubs.h"
}
#include <stdexcept>

double cyl_bessel_k(double nu, double x)
{
    double z[2] = {x, 0.};
    int kode = 1;
    int n = 1;
    double cy[2] = {std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()};
    int nz = 1;
    int ierr = 0;

    zbesk_(&z[0], &z[1], &nu, &kode, &n, &cy[0], &cy[1], &nz, &ierr);

    if (ierr)
    {
        if (ierr == 3)
        {
            throw std::runtime_error("Large arguments -> precision loss (of at least half machine accuracy)");
        }
        else if (ierr == 2)
        {
            throw std::runtime_error("Overflow!");
        }
        else if (ierr == 4)
        {
            throw std::runtime_error("|x| or nu too large");
        }
        else
        {
            throw std::runtime_error("Unexpected error");
        }
    }
    return cy[0];
}
