/**
 * \file qwwad-fileio.h
 *
 * \brief Convenience functions for reading common data from files
 *
 * \author Paul Harrison  <p.harrison@shu.ac.uk>
 * \author Alex Valavanis <a.valavanis@leeds.ac.uk>
 */

#ifndef QWWAD_FILEIO_H
#define QWWAD_FILEIO_H
#include <valarray>

std::valarray<double> read_E(char p);
std::valarray<double> read_populations(int n);
double Vmax();
#endif
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:fileencoding=utf-8:textwidth=99 :