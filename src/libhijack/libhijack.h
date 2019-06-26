#include<libdrakvuf/libdrakvuf.h>
#include<libinjector/libinjector.h>
#include<gmodule.h>

#ifdef __cplusplus
extern "C" {
#endif
struct hijacker {
    drakvuf_t drakvuf;
    vmi_pid_t target_pid;
    char *function_name;
    bool global_search;
    bool is32bit;
    x86_registers_t saved_regs;
    status_type_t status;
    addr_t exec_func;
    json_object* driver_rekall_profile_json;
    drakvuf_trap_t bp;
    GMutex *h_d_mutex;
    bool *spin_lock;
};
typedef struct hijacker* hijacker_t;

bool hijack_get_driver_function_rva(hijacker_t hijacker, char * function_name, addr_t *rva);

bool setup_KeBugCheckEx_stack(hijacker_t hijacker, drakvuf_trap_info_t *info);

bool setup_add1_stack(hijacker_t hijacker, drakvuf_trap_info_t *info);

int hijack(drakvuf_t drakvuf, vmi_pid_t hijack_pid,
                      char *hijack_function, 
                      char *driver_rekall_profile,
                      char *lib_name,
                      GMutex *lock,
                      bool *spin_lock) ;

json_object *hijack_get_modules(json_object* candidates);
int hijack_get_num_modules(json_object *modules);

char * hijack_get_module_name(json_object* module);
char * hijack_get_module_rekall_profile(json_object *module);
json_object * hijack_get_functions(json_object *module);
int hijack_get_num_functions(json_object *module);

char * hijack_get_fucntion_name(json_object *function);
json_object * hijack_get_arguments(json_object *function);
int hijack_get_num_arguments(json_object *function);

char * hijack_get_argument_type(json_object *arg, int idx);


#ifdef __cplusplus
}
#endif

