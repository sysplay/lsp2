#ifndef EM_REGISTERS_H
#define EM_REGISTERS_H

struct em_registers
{
    unsigned int reg_id;
    unsigned int va;
    unsigned int vb;
    unsigned int vc;
    unsigned int va_max;
    unsigned int vb_max;
    unsigned int vc_max;
    unsigned int vavg_max;
    unsigned int va_th;
    unsigned int vb_th;
    unsigned int vc_th;
    unsigned int freq;
    unsigned int ia; 
    unsigned int ib; 
    unsigned int ic; 
    unsigned int i_avg_max;
    unsigned int ia_max;
    unsigned int ib_max;
    unsigned int ic_max;
    unsigned int kw_a;
    unsigned int kw_b;
    unsigned int kw_c;
    unsigned int kw_max;
};

#endif
