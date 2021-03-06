/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "complex.h"

bool_t
xdr_complex (XDR *xdrs, complex *objp)
{
	register int32_t *buf;


	if (xdrs->x_op == XDR_ENCODE) {
		buf = XDR_INLINE (xdrs, 5 * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_int (xdrs, &objp->first_real))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->first_imag))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->second_real))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->second_imag))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->option))
				 return FALSE;
		} else {
			IXDR_PUT_LONG(buf, objp->first_real);
			IXDR_PUT_LONG(buf, objp->first_imag);
			IXDR_PUT_LONG(buf, objp->second_real);
			IXDR_PUT_LONG(buf, objp->second_imag);
			IXDR_PUT_LONG(buf, objp->option);
		}
		return TRUE;
	} else if (xdrs->x_op == XDR_DECODE) {
		buf = XDR_INLINE (xdrs, 5 * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_int (xdrs, &objp->first_real))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->first_imag))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->second_real))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->second_imag))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->option))
				 return FALSE;
		} else {
			objp->first_real = IXDR_GET_LONG(buf);
			objp->first_imag = IXDR_GET_LONG(buf);
			objp->second_real = IXDR_GET_LONG(buf);
			objp->second_imag = IXDR_GET_LONG(buf);
			objp->option = IXDR_GET_LONG(buf);
		}
	 return TRUE;
	}

	 if (!xdr_int (xdrs, &objp->first_real))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->first_imag))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->second_real))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->second_imag))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->option))
		 return FALSE;
	return TRUE;
}
