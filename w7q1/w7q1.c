#include<stdio.h>
#include<stdlib.h>
#include<CL/cl.h>

#define MAX_SOURCE_SIZE (0x100000)

#define WA 2
#define HA 2
#define WB 2
#define HB 2
#define WC 2
#define HC 2
#define BLOCK_SIZE 1

int main(void){

	unsigned int sizeA = WA * HA;
	unsigned int sizeB = WB * HB;
	int *a = (int*)malloc(sizeA * sizeof(int));
	int *b = (int*)malloc(sizeB * sizeof(int));
	int i;

	FILE *fp;
	char *source_str;
	size_t source_size;

	fp = fopen("matrixKernel.cl","r");
	if(!fp){

		fprintf(stderr,"Failed to load Kernel\n");
		exit(1);
	}

	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str,1,MAX_SOURCE_SIZE,fp);

	fclose(fp);

	for(i = 0; i < sizeA; i++)
		scanf("%d",&a[i]);

	for(i = 0; i < sizeB; i++)
			scanf("%d",&b[i]);

	unsigned int sizeC = WC * HC;
	int *c = (int*)malloc(sizeC * sizeof(int));
	for(i = 0; i < sizeC; i++) c[i] = 0;

	//get platform and device information
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1,&platform_id,&ret_num_platforms);
	ret = clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_GPU,1,&device_id,&ret_num_devices);

	//create an OpenCL context
	cl_context context = clCreateContext(NULL,1,&device_id,NULL,NULL,&ret);

	//create a command queue
	cl_command_queue command_queue = clCreateCommandQueue(context,device_id,NULL,&ret);

	//create memory buffers on the device for vectors A,B,C
	cl_mem a_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,sizeA*sizeof(int),NULL,&ret);
	cl_mem b_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,sizeB*sizeof(int),NULL,&ret);
	cl_mem c_mem_obj = clCreateBuffer(context,CL_MEM_WRITE_ONLY,sizeC*sizeof(int),NULL,&ret);

	//Copy the lists A and B to their respective memory buffers
	ret = clEnqueueWriteBuffer(command_queue,a_mem_obj,CL_TRUE,0,sizeA*sizeof(int),a,0,NULL,NULL);
	ret = clEnqueueWriteBuffer(command_queue,b_mem_obj,CL_TRUE,0,sizeB*sizeof(int),b,0,NULL,NULL);

	//Create a program from the kernel source
	cl_program program = clCreateProgramWithSource(context,1,(const char**)&source_str,(const size_t*)&source_size,&ret);

	//Build the program
	ret = clBuildProgram(program,1,&device_id,NULL,NULL,NULL);

	//Create the OpenCL kernel
	cl_kernel kernel = clCreateKernel(program,"matrix_mul",&ret);

	//set the arguments of the kernel
	int widthA = WA; int widthB = WB;

	ret = clSetKernelArg(kernel,0,sizeof(cl_mem),(void*)&a_mem_obj);
	ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void*)&b_mem_obj);
	ret = clSetKernelArg(kernel,2,sizeof(cl_mem),(void*)&c_mem_obj);
	ret = clSetKernelArg(kernel,3,sizeof(cl_int),(void*)&widthA);
	ret = clSetKernelArg(kernel,4,sizeof(cl_int),(void*)&widthB);

	//execute the OpenCL kernel on the array
	size_t globalWorkSize[2] = {WC,HC};
	size_t localWorkSize[2] = {BLOCK_SIZE,BLOCK_SIZE};

	//execute the kernel on the device
	cl_event event;
	ret = clEnqueueNDRangeKernel(command_queue,kernel,2,NULL,globalWorkSize,localWorkSize,0,NULL,&event);

	//read the memory buffer C on the device to the local var C
	ret = clEnqueueReadBuffer(command_queue,c_mem_obj,CL_TRUE,0,sizeC*sizeof(int),c,0,NULL,NULL);

	//display the results to the screen
	printf("Matrix C\n");
	for(i=0; i<sizeC; i++)
	{
		printf("%d\t",c[i]);
		if((i+1) % WC == 0)
			printf("\n");
	}

	//clean up
	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(a_mem_obj);
	ret = clReleaseMemObject(b_mem_obj);
	ret = clReleaseMemObject(c_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	free(source_str);
	free(a); free(b); free(c);
	getchar();
	return 0;

}
