/*
 * This is a Python interface over Simon Josefsson's libidn
 * <URL:http://josefsson.org/libidn/>.
 *
 * Stephane Bortzmeyer <bortzmeyer@nic.fr>
 *
 * $Id$
 */

#include <Python.h>
#include <string.h>
#include <idna.h>

#define MESSAGE_SIZE 512

static PyObject *IDNError;
static PyObject *IDNInvLengthError;

#define onError(message) { PyErr_SetString(IDNError, message); free(message); return NULL; }

static PyObject *
idn2ace (PyObject * self, PyObject * args)
{
  char *instr, *result;
  int rc;
  PyObject *outstr;
  if (!PyArg_ParseTuple (args, "s", &instr))
    onError ("Invalid argument");
  rc = idna_utf8_to_ace (instr, &result);
  if (rc != IDNA_SUCCESS)
    {
      switch (rc)
	{
	case IDNA_INVALID_LENGTH:
	  result = malloc (MESSAGE_SIZE);
	  sprintf (result, "%d bytes", strlen (instr));
	  PyErr_SetString (IDNInvLengthError, result);
	  free (result);
	  return NULL;
	  break;
	default:
	  result = malloc (MESSAGE_SIZE);
	  sprintf (result, "IDN error: %d (see idna.h)", rc);
	  onError (result);
	}
    }
  outstr = Py_BuildValue ("s", result);
  return outstr;
}

static PyObject *
ace2idn (PyObject * self, PyObject * args)
{
  char *instr, *result;
  int rc;
  PyObject *outstr;
  if (!PyArg_ParseTuple (args, "s", &instr))
    onError ("Invalid argument");
  rc = idna_utf8ace_to_utf8 (instr, &result);
  if (rc != IDNA_SUCCESS)
    {
      result = malloc (MESSAGE_SIZE);
      sprintf (result, "IDN error: %d (see idna.h)", rc);
      onError (result);
    }
  outstr = Py_BuildValue ("s", result);
  return outstr;
}

static struct PyMethodDef methods[] = {
  {"idn2ace", idn2ace, 1},
  {"ace2idn", ace2idn, 1},
  {NULL, NULL}
};

void
initidn ()
{
  Py_InitModule ("idn", methods);
  IDNError = PyErr_NewException ("idn.error", NULL, NULL);
  IDNInvLengthError = PyErr_NewException ("idn.invalidLength", NULL, NULL);
}
