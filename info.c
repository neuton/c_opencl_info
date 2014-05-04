#include "cl_error.h"
#include <stdio.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

void show_device_info(cl_device_id device)
{
	cl_bool b;
	cl_ulong l;
	cl_uint u;
	size_t t;
	cl_device_type device_type;
	cl_device_fp_config fp, min_fp;
	cl_device_exec_capabilities dec;
	cl_device_local_mem_type lmt;
	char str[1024];
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_AVAILABLE, sizeof(cl_bool), &b, NULL), "getting device availability"))
		if (b == CL_TRUE) puts("> device IS AVAILABLE"); else puts("> device NOT AVAILABLE");
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(cl_device_type), &device_type, NULL), "getting device type"))
	switch (device_type)
	{
		case CL_DEVICE_TYPE_CPU: puts("> device type: CPU"); break;
		case CL_DEVICE_TYPE_GPU: puts("> device type: GPU"); break;
		case CL_DEVICE_TYPE_ACCELERATOR: puts("> device type: ACCELERATOR"); break;
		default: puts("> device type: UNKNOWN");
	}
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_NAME, 1024, str, NULL), "getting device name"))
		printf("> device name: %s\n", str);
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_VENDOR, 1024, str, NULL), "getting device vendor"))
		printf("> device vendor: %s\n", str);
	
	/*if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_VENDOR_ID, sizeof(cl_uint), &u, NULL), "getting device vendor id"))
		printf("> vendor ID: %u\n", u);*/
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_VERSION, 1024, str, NULL), "getting device version"))
		printf("> OpenCL device version supported: %s\n", str);
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_OPENCL_C_VERSION, 1024, str, NULL), "getting device OpenCL C version"))
		printf("> OpenCL C version supported: %s\n", str);
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_COMPILER_AVAILABLE, sizeof(cl_bool), &b, NULL), "getting compiler availability"))
		if (b == CL_TRUE) puts("> OpenCL compiler IS AVAILABLE"); else puts("> OpenCL compiler NOT AVAILABLE");
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &l, NULL), "getting device global memory size"))
		printf("> global memory size: %llu MB (%llu bytes)\n", l/(1024*1024), l);
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, sizeof(cl_ulong), &l, NULL), "getting device global memory cache size"))
		printf("> global memory cache size: %llu KB (%llu bytes)\n", l/1024, l);
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, sizeof(cl_uint), &u, NULL), "getting device global memory cache line size"))
		printf("> global memory cache line size: %u bytes\n", u);
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_TYPE, sizeof(cl_device_local_mem_type), &lmt, NULL), "getting device local memory type"))
		if (lmt == CL_LOCAL) puts("> local memory type: local"); else puts("> local memory type: global");
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(cl_ulong), &l, NULL), "getting device local memory arena"))
		printf("> local memory arena: %llu KB (%llu bytes)\n", l/1024, l);
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_uint), &u, NULL), "getting device maximum configured clock frequency"))
		printf("> maximum configured clock frequency: %u MHz\n", u);
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &u, NULL), "getting device number of parallel compute cores"))
		printf("> number of parallel compute cores: %u\n", u);
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_PROFILING_TIMER_RESOLUTION, sizeof(size_t), &t, NULL), "getting resolution of device timer"))
		printf("> resolution of device timer: %u ns\n", t);
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &t, NULL), "getting maximum number of work-items in a work-group"))
		printf("> maximum number of work-items in a work-group: %u\n", t);
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), &u, NULL), "getting maximum work-item dimensions"))
		printf("> maximum work-item dimensions: %u\n", u);
	
	size_t ta[u];
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, u * sizeof(size_t), ta, NULL), "getting maximum work-group sizes"))
	{
		printf("> maximum work-group sizes: %u", ta[0]);
		for (u--; u>0; u--) printf(" x %u", ta[u]); printf("\n");
	}
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(cl_ulong), &l, NULL), "getting maximum size of memory object allocation"))
		printf("> maximum size of memory object allocation: %llu MB (%llu bytes)\n", l/(1024*1024), l);
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_MAX_PARAMETER_SIZE, sizeof(size_t), &t, NULL), "getting maximum size of arguments passed to a kernel"))
		printf("> maximum size of arguments passed to a kernel: %u bytes\n", t);
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_HALF_FP_CONFIG, sizeof(cl_device_fp_config), &fp, NULL), "getting half precision floating-point capability"))
	{
		min_fp = CL_FP_ROUND_TO_ZERO | CL_FP_ROUND_TO_INF | CL_FP_INF_NAN;
		printf("> half precision floating-point capability: ");
		if ((min_fp & (min_fp ^ fp)) == 0) puts("YES"); else puts("NO");
	}
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_SINGLE_FP_CONFIG, sizeof(cl_device_fp_config), &fp, NULL), "getting single precision floating-point capability"))
	{
		min_fp = CL_FP_ROUND_TO_NEAREST | CL_FP_INF_NAN;
		printf("> single precision floating-point capability: ");
		if ((min_fp & (min_fp ^ fp)) == 0) puts("YES"); else puts("NO");
	}
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_DOUBLE_FP_CONFIG, sizeof(cl_device_fp_config), &fp, NULL), "getting double precision floating-point capability"))
	{
		min_fp = CL_FP_FMA | CL_FP_ROUND_TO_NEAREST | CL_FP_ROUND_TO_ZERO | CL_FP_ROUND_TO_INF | CL_FP_INF_NAN | CL_FP_DENORM;
		printf("> double precision floating-point capability: ");
		if ((min_fp & (min_fp ^ fp)) == 0) puts("YES"); else puts("NO");
	}
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_ERROR_CORRECTION_SUPPORT, sizeof(cl_bool), &b, NULL), "getting error correction support"))
	{
		printf("> error correction support: ");
		if (b == CL_TRUE) puts("YES"); else puts("NO");
	}
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_EXECUTION_CAPABILITIES, sizeof(cl_device_exec_capabilities), &dec, NULL), "getting kernels execution capability"))
	{
		printf("> can execute OpenCL kernels: ");
		if (dec & CL_EXEC_KERNEL) puts("YES"); else puts("NO");
		printf("> can execute native kernels: ");
		if (dec & CL_EXEC_NATIVE_KERNEL) puts("YES"); else puts("NO");
	}
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_IMAGE_SUPPORT, sizeof(cl_bool), &b, NULL), "getting images support"))
	{
		printf("> images support: ");
		if (b == CL_TRUE) puts("YES"); else puts("NO");
	}
	
	if (!clSoftCheckError(clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, 1024, str, NULL), "getting list of supported extensions"))
	{
		puts("> list of supported extensions:");
		puts(str);
	}
}

int main()
{
	const cl_uint n_max = 16;
	cl_uint i, j, n_platforms, n_devices;
	cl_platform_id platforms[n_max];
	cl_device_id devices[n_max];
	clCheckError(clGetPlatformIDs(0, NULL, &n_platforms), "getting number of available platforms");	// seems strange: here first argument may be not 0, but not in clGetDeviceIDs
	clCheckError(clGetPlatformIDs(n_platforms, platforms, NULL), "getting available platforms' IDs");
	for (i=0; i<n_platforms; i++)
	{
		printf("\n============= Platform #%u =============\n", i+1);
		if (!clSoftCheckError(clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &n_devices), "getting number of available devices"))	// here the third argument must be 0
		{
			if (!clSoftCheckError(clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, n_devices, devices, NULL), "getting available devices' IDs"))
				for (j=0; j<n_devices; j++)
				{
					printf("\n============== Device #%u ==============\n", j+1);
					show_device_info(devices[j]);
				}
		}
	}
	return 0;
}
