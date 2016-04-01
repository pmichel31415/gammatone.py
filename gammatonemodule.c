/*
 *=========================================================================
 * Python wrapper for Ning Ma's optimized gammatone filter C implementation
 *-------------------------------------------------------------------------
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *-------------------------------------------------------------------------
 * Paul Michel, ENS LSCP, pmichel31415@gmail.com
 *-------------------------------------------------------------------------
 */
#include <Python.h>
#include "gammatone.h"

#define DOCSTRING "The gammatone filter is commonly used in models of the auditory system.\nThe algorithm is based on Martin Cooke's Ph.D work (Cooke, 1993) using\nthe base-band impulse invariant transformation. This implementation is\nhighly efficient in that a mathematical rearrangement is used to\nsignificantly reduce the cost of computing complex exponentials. For\nmore detail on this implementation see\nhttp://www.dcs.shef.ac.uk/~ning/resources/gammatone/\n\n:param x:     - input signal\n:param fs:    - sampling frequency (Hz)\n:param cf:    - centre frequency of the filter (Hz)\n:param hrect: - half-wave rectifying if hrect = 1 (default 0)\n:returns: (bm,env,instp,instf)\n   bm:    - basilar membrane displacement\n   env:   - instantaneous envelope\n   instp: - instantaneous phase (unwrapped radian)\n   instf: - instantaneous frequency (Hz)"

static PyObject *gammatone_wrapper(PyObject *self, PyObject *args) {

    PyObject *in_x, *out_bm, *out_env, *out_instp, *out_instf;
    PyObject *float_obj;
    double *x, *bm, *env, *instp, *instf;
    double cf;
    int i, fs, nsamples, hrect = 0;

    /*=========================================
     * input arguments
     *=========================================
     */
    if (!PyArg_ParseTuple(args, "O!id|i", &PyList_Type, &in_x, &fs, &cf, &hrect)) {
        return NULL;
    }

    nsamples = PyList_Size(in_x);
    if (nsamples < 0)   return NULL;

    x = (double*)calloc(nsamples, sizeof(double));

    for (i = 0; i < nsamples; i++) {
        float_obj = PyList_GetItem(in_x, i);
        x[i] = PyFloat_AsDouble( float_obj );
    }

    /*=========================================
     * dark magic
     *=========================================
     */

    gammatone(x, nsamples, fs, cf, hrect, &bm, &env, &instp, &instf);

    /*=========================================
     * output arguments
     *=========================================
     */

    out_bm = PyList_New(nsamples);
    out_env = PyList_New(nsamples);
    out_instp = PyList_New(nsamples);
    out_instf = PyList_New(nsamples);

    for (i = 0; i < nsamples; i++) {
        float_obj = PyFloat_FromDouble(bm[i]);
        PyList_SET_ITEM(out_bm, i, float_obj);

        float_obj = PyFloat_FromDouble(env[i]);
        PyList_SET_ITEM(out_env, i, float_obj);

        float_obj = PyFloat_FromDouble(instp[i]);
        PyList_SET_ITEM(out_instp, i, float_obj);

        float_obj = PyFloat_FromDouble(instf[i]);
        PyList_SET_ITEM(out_instf, i, float_obj);
    }

    /*=========================================
     * free memory
     *=========================================
     */

    free(x);
    free(bm);
    free(env);
    free(instp);
    free(instf);

    return Py_BuildValue("OOOO", out_bm, out_env, out_instp, out_instf);

}

static PyMethodDef gammatone_methods[] = {
    { "gammatone", (PyCFunction)gammatone_wrapper, METH_VARARGS, DOCSTRING },
    { NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC initgammatone(void) {
    Py_InitModule3("gammatone", gammatone_methods, "Python wrapper around Ning Ma\'s gammatone filter optimized C implementation.");
}