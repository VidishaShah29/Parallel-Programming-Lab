//MxN matrix
//replace ith row elements by a^i of each element

#include<stdio.h>
#include<stdlib.h>
#include<CL/cl.h>

#define MAX_SOURCE_SIZE (0x100000)

#define BLOCK_SIZE 1

int main(void){

	int m,n;
	printf("Enter size MxN: ");
	scanf("%d%d",&m,&n);
	unsigned int sizeA = m * n;
	int *a = (int*)malloc(sizeA * sizeof(int));
	int i;

	FILE *fp;
	char *source_str;
	size_t source_size;

	fp = fopen("q1w7.cl","r");
	if(!fp){

		fprintf(stderr,"Failed to load Kernel\n");
		exit(1);
	}

	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str,1,MAX_SOURCE_SIZE,fp);

	fclose(fp);

	printf("Enter Matrix: ");

	for(i = 0; i < sizeA; i++)
		scanf("%d",&a[i]);

	unsigned int sizeC = m * n;
	int *c = (int*)malloc(sizeC * sizeof(int));

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
	cl_mem c_mem_obj = clCreateBuffer(context,CL_MEM_WRITE_ONLY,sizeC*sizeof(int),NULL,&ret);

	//Copy the lists A and B to their respective memory buffers
	ret = clEnqueueWriteBuffer(command_queue,a_mem_obj,CL_TRUE,0,sizeA*sizeof(int),a,0,NULL,NULL);

	//Create a program from the kernel source
	cl_program program = clCreateProgramWithSource(context,1,(const char**)&source_str,(const size_t*)&source_size,&ret);

	//Build the program
	ret = clBuildProgram(program,1,&device_id,NULL,NULL,NULL);

	//Create the OpenCL kernel
	cl_kernel kernel = clCreateKernel(program,"matrix",&ret);

	ret = clSetKernelArg(kernel,0,sizeof(cl_mem),(void*)&a_mem_obj);
	ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void*)&c_mem_obj);
	ret = clSetKernelArg(kernel,2,sizeof(cl_int),(void*)&m);
	ret = clSetKernelArg(kernel,3,sizeof(cl_int),(void*)&n);


	//execute the OpenCL kernel on the array
	size_t globalWorkSize[2] = {m,n};
	size_t localWorkSize[2] = {BLOCK_SIZE,BLOCK_SIZE};

	//execute the kernel on the device
	cl_event event;
	ret = clEnqueueNDRangeKernel(command_queue,kernel,2,NULL,globalWorkSize,localWorkSize,0,NULL,&event);

	//read the memory buffer C on the device to the local var C
	ret = clEnqueueReadBuffer(command_queue,c_mem_obj,CL_TRUE,0,sizeC*sizeof(int),c,0,NULL,NULL);

	//display the results to the screen
	printf("Output Matrix\n");
	for(i=0; i<sizeC; i++)
	{
		printf("%d\t",c[i]);
		if((i+1) % n == 0)
			printf("\n");
	}

	//clean up
	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(a_mem_obj);
	ret = clReleaseMemObject(c_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	free(source_str);
	free(a); free(c);
	getchar();
	return 0;

}

