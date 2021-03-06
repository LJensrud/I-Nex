#include <stdio.h>
#include <libcpuid.h>
int main(void)
{
	if (!cpuid_present()) {                                                // check for CPUID presence
		printf("Sorry, your CPU doesn't support CPUID!\n");
		return -1;
	}
	struct cpu_raw_data_t raw;                                             // contains only raw data
	struct cpu_id_t data;                                                  // contains recognized CPU features data
	if (cpuid_get_raw_data(&raw) < 0) {                                    // obtain the raw CPUID data
		printf("Sorry, cannot get the CPUID raw data.\n");
		printf("Error: %s\n", cpuid_error());                          // cpuid_error() gives the last error description
		return -2;
	}
	if (cpu_identify(&raw, &data) < 0) {                                   // identify the CPU, using the given raw data.
		printf("Sorrry, CPU identification failed.\n");
		printf("Error: %s\n", cpuid_error());
		return -3;
	}
	/**int a, b;
 
	for (a = 0; a < 5; a++)
	{
	  __asm__("cpuid"
            :"=a"(b)                 // EAX into b (output)
            :"0"(a)                  // a into EAX (input)
            :"%ebx","%ecx","%edx");  // clobbered registers
 
	printf("The code %i gives %i\n", a, b);
	}*/
	struct cpu_mark_t mark;
	cpu_tsc_mark(&mark);
	cpu_tsc_unmark(&mark);
	printf("{\n");
	printf("	\"VENDOR_STR\": \"%s\",\n", data.vendor_str);	              //
	printf("	\"CPU_CODENAME\": \"%s\",\n", data.cpu_codename);	      //
	printf("	\"BRAND_STR\": \"%s\",\n", data.brand_str);		      //
	printf("	\"NUM_CORES\": \"%d\",\n", data.num_cores);		      //
	printf("	\"NUM_LOGICAL_CPUS\": \"%d\",\n", data.num_logical_cpus);     //
	printf("	\"TOTAL_LOGICAL_CPUS\": \"%d\",\n", data.total_logical_cpus); //
	printf("	\"FAMILY\": \"%d\",\n", data.family);                         //
	printf("	\"MODEL\": \"%d\",\n", data.model);                           //
	printf("	\"STEPPING\": \"%d\",\n", data.stepping);                     //
	printf("	\"EXT_FAMILY\": \"%d\",\n", data.ext_family);                 //
	printf("	\"EXT_MODEL\": \"%d\",\n", data.ext_model);                   //
	printf("	\"CPU_CLOCK\": \"%d\",\n", cpu_clock());                      //
	printf("	\"CPU_CLOCK_BY_OS\": \"%d\",\n", cpu_clock_by_os());          //
	printf("	\"CPU_CLOCK_BY_IC\": \"%d\",\n", cpu_clock_by_ic(200, 0));    //
	printf("	\"CPU_CLOCK_MEASURE\": \"%d\",\n", cpu_clock_measure(200, 0));//
	printf("	\"MARK_TSC\": \"%llu\",\n", mark.tsc);			      //
	printf("	\"MARK_SYS_CLOCK\": \"%llu\",\n", mark.sys_clock);            //
	printf("			\"Flags\": {\n");
	printf("			\"1\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_MMXEXT] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_MMXEXT\",\n");
	printf("					\"FEATURE\": \"mmxext\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/MMX_(instruction_set)\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"AMD MMX-extended instructions supported\"\n");
	printf("			},\n");
	printf("			\"2\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_SSE] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_SSE\",\n");
	printf("					\"FEATURE\": \"sse\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Streaming_SIMD_Extensions\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Streaming-SIMD Extensions (SSE) supported\"\n");
	printf("			},\n");
	printf("			\"3\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_SSE2] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_SSE2\",\n");
	printf("					\"FEATURE\": \"sse2\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/SSE2\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"SSE2 instructions supported\"\n");
	printf("			},\n");
	printf("			\"4\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_3DNOW] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_3DNOW\",\n");
	printf("					\"FEATURE\": \"3dnow\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/3DNow!\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"AMD 3DNow! instructions supported\"\n");
	printf("			},\n");
	printf("			\"5\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_VME] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_VME\",\n");
	printf("					\"FEATURE\": \"vme\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Virtual_8086_mode\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Virtual mode extension\"\n");
	printf("			},\n");
	printf("			\"6\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_CLFLUSH] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_CLFLUSH\",\n");
	printf("					\"FEATURE\": \"clflush\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"CLFLUSH instruction supported\"\n");
	printf("			},\n");
	printf("			\"7\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_SSSE3] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_SSSE3\",\n");
	printf("					\"FEATURE\": \"ssse3\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/SSE3\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"SSSE3 instructionss supported (this is different from SSE3!)\"\n");
	printf("			},\n");
	printf("			\"8\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_LM] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_LM\",\n");
	printf("					\"FEATURE\": \"lm\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Long mode (x86_64/EM64T) supported\"\n");
	printf("			},\n");
	printf("			\"9\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_LAHF_LM] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_LAHF_LM\",\n");
	printf("					\"FEATURE\": \"lahf_lm\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"LAHF/SAHF supported in 64-bit mode\"\n");
	printf("			},\n");
	printf("			\"10\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_MTRR] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_MTRR\",\n");
	printf("					\"FEATURE\": \"mtrr\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Memory_type_range_register\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Memory type range registers\"\n");
	printf("			},\n");
	printf("			\"11\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_ACPI] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_ACPI\",\n");
	printf("					\"FEATURE\": \"acpi\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Acpi\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"ACPI support (power states)\"\n");
	printf("			},\n");
	printf("			\"12\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_VMX] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_VMX\",\n");
	printf("					\"FEATURE\": \"vmx\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/X86_virtualization\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Virtualization technology supported\"\n");
	printf("			},\n");
	printf("			\"13\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_SYSCALL] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_SYSCALL\",\n");
	printf("					\"FEATURE\": \"syscall\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Syscall\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"SYSCALL / SYSRET instructions supported\"\n");
	printf("			},\n");
	printf("			\"14\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_DTS64] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_DTS64\",\n");
	printf("					\"FEATURE\": \"dts64\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"64-bit Debug store supported\"\n");
	printf("			},\n");
	printf("			\"15\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_FPU] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_FPU\",\n");
	printf("					\"FEATURE\": \"fpu\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Floating-point_unit\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Floating point unit\"\n");
	printf("			},\n");
	printf("			\"16\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_DE] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_DE\",\n");
	printf("					\"FEATURE\": \"de\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Debugging extension\"\n");
	printf("			},\n");
	printf("			\"17\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_VME] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_VME\",\n");
	printf("					\"FEATURE\": \"vme\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Virtual_8086_mode\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Virtual mode extension\"\n");
	printf("			},\n");
	printf("			\"18\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_PSE] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_PSE\",\n");
	printf("					\"FEATURE\": \"pse\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Page_Size_Extension\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Page size extension\"\n");
	printf("			},\n");
	printf("			\"19\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_TSC] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_TSC\",\n");
	printf("					\"FEATURE\": \"tsc\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Time_Stamp_Counter\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Time-stamp counter\"\n");
	printf("			},\n");
	printf("			\"20\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_MSR] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_MSR\",\n");
	printf("					\"FEATURE\": \"msr\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Model-specific_register\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Model-specific regsisters, RDMSR/WRMSR supported\"\n");
	printf("			},\n");
	printf("			\"21\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_PAE] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_PAE\",\n");
	printf("					\"FEATURE\": \"pae\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Physical_Address_Extension\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Physical address extension\"\n");
	printf("			},\n");
	printf("			\"22\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_MCE] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_MCE\",\n");
	printf("					\"FEATURE\": \"mce\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Machine-check_exception\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Machine check exception\"\n");
	printf("			},\n");
	printf("			\"23\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_CX8] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_CX8\",\n");
	printf("					\"FEATURE\": \"cx8\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"CMPXCHG8B instruction supported\"\n");
	printf("			},\n");
	printf("			\"24\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_APIC] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_APIC\",\n");
	printf("					\"FEATURE\": \"apic\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Advanced_Programmable_Interrupt_Controller\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"APIC support\"\n");
	printf("			},\n");
	printf("			\"25\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_MTRR] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_MTRR\",\n");
	printf("					\"FEATURE\": \"mtrr\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Memory_type_range_register\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Memory type range registers\"\n");
	printf("			},\n");
	printf("			\"26\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_SEP] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_SEP\",\n");
	printf("					\"FEATURE\": \"sep\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Call_gate\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"SYSENTER / SYSEXIT instructions supported\"\n");
	printf("			},\n");
	printf("			\"27\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_PGE] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_PGE\",\n");
	printf("					\"FEATURE\": \"pge\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Translation_lookaside_buffer\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Page global enable\"\n");
	printf("			},\n");
	printf("			\"28\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_MCA] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_MCA\",\n");
	printf("					\"FEATURE\": \"mca\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Machine_check_architecture\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Machine check architecture\"\n");
	printf("			},\n");
	printf("			\"29\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_CMOV] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_CMOV\",\n");
	printf("					\"FEATURE\": \"cmov\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"CMOVxx instructions supported\"\n");
	printf("			},\n");
	printf("			\"30\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_PAT] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_PAT\",\n");
	printf("					\"FEATURE\": \"pat\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Page_attribute_table\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Page attribute table\"\n");
	printf("			},\n");
	printf("			\"31\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_PSE36] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_PSE36\",\n");
	printf("					\"FEATURE\": \"pse36\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Physical_Address_Extension\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"36-bit page address extension\"\n");
	printf("			},\n");
	printf("			\"32\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_PN] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_PN\",\n");
	printf("					\"FEATURE\": \"pt\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Processor serial # implemented (Intel P3 only)\"\n");
	printf("			},\n");
	printf("			\"33\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_DTS] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_DTS\",\n");
	printf("					\"FEATURE\": \"dts\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Debug store supported\"\n");
	printf("			},\n");
	printf("			\"34\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_SS] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_SS\",\n");
	printf("					\"FEATURE\": \"ss\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Ss\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Self-snoop\"\n");
	printf("			},\n");
	printf("			\"35\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_TM] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_TM\",\n");
	printf("					\"FEATURE\": \"tm\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Thermal monitor\"\n");
	printf("			},\n");
	printf("			\"36\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_IA64] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_IA64\",\n");
	printf("					\"FEATURE\": \"ia64\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Ia64\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"IA64 supported (Itanium only)\"\n");
	printf("			},\n");
	printf("			\"37\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_PBE] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_PBE\",\n");
	printf("					\"FEATURE\": \"pbe\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Pending-break enable\"\n");
	printf("			},\n");
	printf("			\"38\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_PNI] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_PNI\",\n");
	printf("					\"FEATURE\": \"pni\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/SSE3\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"PNI (SSE3) instructions supported\"\n");
	printf("			},\n");
	printf("			\"39\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_PCLMUL] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_PCLMUL\",\n");
	printf("					\"FEATURE\": \"pclmul\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"PCLMULQDQ instruction supported\"\n");
	printf("			},\n");
	printf("			\"40\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_MONITOR] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_MONITOR\",\n");
	printf("					\"FEATURE\": \"monitor\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"MONITOR / MWAIT supported\"\n");
	printf("			},\n");
	printf("			\"41\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_DS_CPL] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_DS_CPL\",\n");
	printf("					\"FEATURE\": \"ds_cpl\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"CPL Qualified Debug Store\"\n");
	printf("			},\n");
	printf("			\"42\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_SMX] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_SMX\",\n");
	printf("					\"FEATURE\": \"smx\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/LaGrande\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Safer mode exceptions\"\n");
	printf("			},\n");
	printf("			\"43\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_EST] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_EST\",\n");
	printf("					\"FEATURE\": \"est\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/SpeedStep\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Enhanced SpeedStep\"\n");
	printf("			},\n");
	printf("			\"44\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_TM2] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_TM2\",\n");
	printf("					\"FEATURE\": \"tm2\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Tm2\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Thermal monitor 2\"\n");
	printf("			},\n");
	printf("			\"45\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_CID] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_CID\",\n");
	printf("					\"FEATURE\": \"cid\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Context ID supported\"\n");
	printf("			},\n");
	printf("			\"46\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_CX16] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_CX16\",\n");
	printf("					\"FEATURE\": \"cx16\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"CMPXCHG16B instruction supported\"\n");
	printf("			},\n");
	printf("			\"47\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_XTPR] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_XTPR\",\n");
	printf("					\"FEATURE\": \"xtpr\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Send Task Priority Messages disable\"\n");
	printf("			},\n");
	printf("			\"48\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_PDCM] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_PDCM\",\n");
	printf("					\"FEATURE\": \"pdcm\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Performance capabilities MSR supported\"\n");
	printf("			},\n");
	printf("			\"49\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_DCA] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_DCA\",\n");
	printf("					\"FEATURE\": \"dca\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Direct cache access supported\"\n");
	printf("			},\n");
	printf("			\"50\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_SSE4_1] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_SSE4_1\",\n");
	printf("					\"FEATURE\": \"sse4_1\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/SSE4\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"SSE 4.1 instructions supported\"\n");
	printf("			},\n");
	printf("			\"51\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_SSE4_2] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_SSE4_2\",\n");
	printf("					\"FEATURE\": \"sse4_2\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/SSE4\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"SSE 4.2 instructions supported\"\n");
	printf("			},\n");
	printf("			\"52\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_SYSCALL] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_SYSCALL\",\n");
	printf("					\"FEATURE\": \"syscall\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"SYSCALL / SYSRET instructions supported\"\n");
	printf("			},\n");
	printf("			\"53\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_XD] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_XD\",\n");
	printf("					\"FEATURE\": \"xd\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Execute disable bit supported\"\n");
	printf("			},\n");
	printf("			\"54\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_MOVBE] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_MOVBE\",\n");
	printf("					\"FEATURE\": \"movbe\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"MOVBE instruction supported\"\n");
	printf("			},\n");
	printf("			\"55\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_POPCNT] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_POPCNT\",\n");
	printf("					\"FEATURE\": \"popcnt\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Hamming_weight\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"POPCNT instruction supported\"\n");
	printf("			},\n");
	printf("			\"56\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_AES] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_AES\",\n");
	printf("					\"FEATURE\": \"aes\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/AES_instruction_set\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"AES* instructions supported\"\n");
	printf("			},\n");
	printf("			\"57\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_XSAVE] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_XSAVE\",\n");
	printf("					\"FEATURE\": \"xsave\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Streaming_SIMD_Extensions\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"XSAVE/XRSTOR/etc instructions supported\"\n");
	printf("			},\n");
	printf("			\"58\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_OSXSAVE] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_OSXSAVE\",\n");
	printf("					\"FEATURE\": \"osxsave\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Streaming_SIMD_Extensions\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"non-privileged copy of OSXSAVE supported\"\n");
	printf("			},\n");
	printf("			\"59\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_AVX] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_AVX\",\n");
	printf("					\"FEATURE\": \"avx\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Advanced_Vector_Extensions\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Advanced vector extensions supported\"\n");
	printf("			},\n");
	printf("			\"60\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_3DNOWEXT] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_3DNOWEXT\",\n");
	printf("					\"FEATURE\": \"3dnowext\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/3DNow!\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"AMD 3DNow! extended instructions supported\"\n");
	printf("			},\n");
	printf("			\"61\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_NX] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_NX\",\n");
	printf("					\"FEATURE\": \"nx\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/NX_bit\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"No-execute bit supported\"\n");
	printf("			},\n");
	printf("			\"62\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_FXSR_OPT] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_FXSR_OPT\",\n");
	printf("					\"FEATURE\": \"opt\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"FFXSR: FXSAVE and FXRSTOR optimizations\"\n");
	printf("			},\n");
	printf("			\"63\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_RDTSCP] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_RDTSCP\",\n");
	printf("					\"FEATURE\": \"rdtscp\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Time_Stamp_Counter\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"RDTSCP instruction supported (AMD-only)\"\n");
	printf("			},\n");
	printf("			\"64\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_LM] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_LM\",\n");
	printf("					\"FEATURE\": \"lm\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Long mode (x86_64/EM64T) supported\"\n");
	printf("			},\n");
	printf("			\"65\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_LAHF_LM] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_LAHF_LM\",\n");
	printf("					\"FEATURE\": \"lahf_lm\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"LAHF/SAHF supported in 64-bit mode\"\n");
	printf("			},\n");
	printf("			\"66\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_CMP_LEGACY] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_CMP_LEGACY\",\n");
	printf("					\"FEATURE\": \"cmp_legacy\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Core multi-processing legacy mode\"\n");
	printf("			},\n");
	printf("			\"67\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_SVM] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_SVM\",\n");
	printf("					\"FEATURE\": \"svm\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"AMD Secure virtual machine\"\n");
	printf("			},\n");
	printf("			\"68\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_SSE4A] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_SSE4A\",\n");
	printf("					\"FEATURE\": \"sse4a\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/SSE4\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"SSE 4a from AMD\"\n");
	printf("			},\n");
	printf("			\"69\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_MISALIGNSSE] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_MISALIGNSSE\",\n");
	printf("					\"FEATURE\": \"misalignsse\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Misaligned SSE supported\"\n");
	printf("			},\n");
	printf("			\"70\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_ABM] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_ABM\",\n");
	printf("					\"FEATURE\": \"abm\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Bit_Manipulation_Instruction_Sets\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"LZCNT instruction support\"\n");
	printf("			},\n");
	printf("			\"71\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_3DNOWPREFETCH] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_3DNOWPREFETCH\",\n");
	printf("					\"FEATURE\": \"3dnowprefetch\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/3DNow!\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"PREFETCH/PREFETCHW support\"\n");
	printf("			},\n");
	printf("			\"72\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_OSVW] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_OSVW\",\n");
	printf("					\"FEATURE\": \"osvw\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"OS Visible Workaround (AMD)\"\n");
	printf("			},\n");
	printf("			\"73\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_IBS] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_IBS\",\n");
	printf("					\"FEATURE\": \"ibs\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Hardware_performance_counter\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Instruction-based sampling\"\n");
	printf("			},\n");
	printf("			\"74\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_SSE5] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_SSE5\",\n");
	printf("					\"FEATURE\": \"sse5\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/SSE5\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"SSE 5 instructions supported (deprecated, will never be 1)\"\n");
	printf("			},\n");
	printf("			\"75\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_SKINIT] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_SKINIT\",\n");
	printf("					\"FEATURE\": \"skinit\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"SKINIT / STGI supported\"\n");
	printf("			},\n");
	printf("			\"76\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_WDT] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_WDT\",\n");
	printf("					\"FEATURE\": \"wdt\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Watchdog_timer\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Watchdog timer support\"\n");
	printf("			},\n");
	printf("			\"77\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_TS] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_TS\",\n");
	printf("					\"FEATURE\": \"ts\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Temperature sensor\"\n");
	printf("			},\n");
	printf("			\"78\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_FID] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_FID\",\n");
	printf("					\"FEATURE\": \"fid\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Frequency ID control\"\n");
	printf("			},\n");
	printf("			\"79\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_VID] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_VID\",\n");
	printf("					\"FEATURE\": \"vid\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Voltage ID control\"\n");
	printf("			},\n");
	printf("			\"80\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_TTP] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_TTP\",\n");
	printf("					\"FEATURE\": \"ttp\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"THERMTRIP\"\n");
	printf("			},\n");
	printf("			\"81\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_TM_AMD] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_TM_AMD\",\n");
	printf("					\"FEATURE\": \"tm_amd\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"AMD-specified hardware thermal control\"\n");
	printf("			},\n");
	printf("			\"82\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_STC] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_STC\",\n");
	printf("					\"FEATURE\": \"stc\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Software thermal control\"\n");
	printf("			},\n");
	printf("			\"83\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_100MHZSTEPS] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_100MHZSTEPS\",\n");
	printf("					\"FEATURE\": \"100mhzsteps\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"100 MHz multiplier control\"\n");
	printf("			},\n");
	printf("			\"84\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_HWPSTATE] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_HWPSTATE\",\n");
	printf("					\"FEATURE\": \"hwpstate\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Hardware P-state control\"\n");
	printf("			},\n");
	printf("			\"85\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_CONSTANT_TSC] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_CONSTANT_TSC\",\n");
	printf("					\"FEATURE\": \"constant_tsc\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Time_Stamp_Counter\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"TSC ticks at constant rate\"\n");
	printf("			},\n");
	printf("			\"86\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_XOP] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_XOP\",\n");
	printf("					\"FEATURE\": \"xop\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"The XOP instruction set (same as the old CPU_FEATURE_SSE5)\"\n");
	printf("			},\n");
	printf("			\"87\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_FMA3] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_FMA3\",\n");
	printf("					\"FEATURE\": \"fma3\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/FMA_instruction_set\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"The FMA3 instruction set\"\n");
	printf("			},\n");
	printf("			\"88\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_FMA4] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_FMA4\",\n");
	printf("					\"FEATURE\": \"fma4\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/FMA_instruction_set\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"The FMA4 instruction set\"\n");
	printf("			},\n");
	printf("			\"89\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_TBM] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_TBM\",\n");
	printf("					\"FEATURE\": \"tbm\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"Trailing bit manipulation instruction support\"\n");
	printf("			},\n");
	printf("			\"90\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_F16C] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_F16C\",\n");
	printf("					\"FEATURE\": \"f16c\",\n");
	printf("					\"WEBSITE\": \"mmxext\",\n");
	printf("					\"HAVEWEBSITE\": 0 ,\n");
	printf("					\"DESC\": \"16-bit FP convert instruction support\"\n");
	printf("			},\n");
	printf("			\"91\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_RDRAND] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_RDRAND\",\n");
	printf("					\"FEATURE\": \"rdrand\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/RdRand\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"RdRand instruction\"\n");
	printf("			},\n");
	printf("			\"92\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_HT] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_HT\",\n");
	printf("					\"FEATURE\": \"ht\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/Hyper-Threading\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Hyper-threading supported (but might be disabled)\"\n");
	printf("			},\n");
	printf("			\"93\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_MMX] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_MMX\",\n");
	printf("					\"FEATURE\": \"mmx\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/MMX_(instruction_set)\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"MMX instruction set supported\"\n");
	printf("			},\n");
	printf("			\"94\": {\n");
	printf("					\"VALUE\": %s \n", data.flags[CPU_FEATURE_FPU] ? "1 ," : "0 ,");
	printf("					\"NAME\": \"CPU_FEATURE_FPU\",\n");
	printf("					\"FEATURE\": \"fpu\",\n");
	printf("					\"WEBSITE\": \"http://en.wikipedia.org/wiki/X87\",\n");
	printf("					\"HAVEWEBSITE\": 1 ,\n");
	printf("					\"DESC\": \"Floating point unit\"\n");
	printf("			}\n");
	printf("	},\n");
	printf("	\"L1_DATA_CACHE\": \"%d\",\n", data.l1_data_cache);
	printf("	\"L1_INSTRUCTION_CACHE\": \"%d\",\n", data.l1_instruction_cache);
	printf("	\"L2_CACHE\": \"%d\",\n", data.l2_cache);
	printf("	\"L3_CACHE\": \"%d\",\n", data.l3_cache);
	printf("	\"L1_ASSOC\": \"%d\",\n", data.l1_assoc);
	printf("	\"L2_ASSOC\": \"%d\",\n", data.l2_assoc);
	printf("	\"L3_ASSOC\": \"%d\",\n", data.l3_assoc);
	printf("	\"L1_CACHELINE\": \"%d\",\n", data.l1_cacheline);
	printf("	\"L2_CACHELINE\": \"%d\",\n", data.l2_cacheline);
	printf("	\"L3_CACHELINE\": \"%d\",\n", data.l3_cacheline);
	printf("	\"SSE_SIZE\": \"%d\"\n", data.sse_size);
	printf("}\n");
	return 0;
}