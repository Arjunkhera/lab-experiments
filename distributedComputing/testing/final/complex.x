
struct complex{
  int first_real;
  int first_imag;

  int second_real;
  int second_imag;

  int option;
};

program ARITH_PROG{

  version ARITH_VERS{
    int arith(complex)=1;
  }=1;

}=0x23451122;
