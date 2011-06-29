/*
  * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License (either version 2 or
 * version 3) as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * For more information on the GPL, please go to:
 * http://www.gnu.org/copyleft/gpl.html
 */


// This is just a fast hack for demo usage

// Use at your own risk. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <libusb.h>

#define VID 0x04fc
#define PID 0x1528

#define TIMEOUT 1000

libusb_device_handle *device_handle;

void control_out(int request, int value, int index, unsigned char* buf,
		int length) {

	int n = libusb_control_transfer(device_handle, LIBUSB_ENDPOINT_OUT
			| LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_INTERFACE, request,
			value, index, buf, length, TIMEOUT);

	if (n < 0) {
		fprintf(stderr, "Control transfer failed: ");
		switch (n) {
		case LIBUSB_ERROR_TIMEOUT:
			fprintf(stderr, "transfer timed out");
			break;
		case LIBUSB_ERROR_PIPE:
			fprintf(stderr, "control request was not supported "
				"by the device");
			break;
		case LIBUSB_ERROR_NO_DEVICE:
			fprintf(stderr, "device has been disconnected");
			break;
		default:
			fprintf(stderr, "error %d", n);
			break;
		}
		fprintf(stderr, "\n");
	} else if (n > 0) {
		fprintf(stderr, "Write %d bytes:", n);
		int i;
		for (i = 0; i < n; i++)
			fprintf(stderr, " %02x", buf[i]);
		fprintf(stderr, "\n");

	}
}

void control_in_vendor_device(int request, int value, int index, int length) {
	unsigned char *buf = calloc(length, sizeof(unsigned char));
	int n = libusb_control_transfer(device_handle, LIBUSB_ENDPOINT_IN
			| LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_INTERFACE, request,
			value, index, buf, length, TIMEOUT);
	if (n < 0) {
		fprintf(stderr, "Control transfer failed: ");
		switch (n) {
		case LIBUSB_ERROR_TIMEOUT:
			fprintf(stderr, "transfer timed out");
			break;
		case LIBUSB_ERROR_PIPE:
			fprintf(stderr, "control request was not supported "
				"by the device");
			break;
		case LIBUSB_ERROR_NO_DEVICE:
			fprintf(stderr, "device has been disconnected");
			break;
		default:
			fprintf(stderr, "error %d", n);
			break;
		}
		fprintf(stderr, "\n");
	} else if (n > 0) {
		fprintf(stderr, "Received %d bytes:", n);

		int i;
		for (i = 0; i < n; i++)
			fprintf(stderr, " %02x", buf[i]);
		fprintf(stderr, "\n");
	}
	free(buf);
}

void GetVersion() {
	control_in_vendor_device(0x20, 0, 0, 8);
}

void GetVersion1() {
	control_in_vendor_device(0x20, 0, 1, 8);
}

void GetVersion2() {
	control_in_vendor_device(0x20, 0, 2, 8);

}
void bulk_transfer_error(int code) {
	fprintf(stderr, "Bulk transfer failed: ");
	switch (code) {
	case LIBUSB_ERROR_TIMEOUT:
		fprintf(stderr, "transfer timed out");
		break;
	case LIBUSB_ERROR_PIPE:
		fprintf(stderr, "endpoint halted");
		break;
	case LIBUSB_ERROR_OVERFLOW:
		fprintf(stderr, "device sent too much data");
		break;
	case LIBUSB_ERROR_NO_DEVICE:
		fprintf(stderr, "device has been disconnected");
		break;
	default:
		fprintf(stderr, "error %d", code);
		break;
	}
	fprintf(stderr, "\n");
}

int bulk_read(int endpoint, unsigned char *buf, int length) {
	int ret, n;
	if ((ret = libusb_bulk_transfer(device_handle, LIBUSB_ENDPOINT_IN
			| endpoint, buf, length, &n, TIMEOUT)) < 0)
		bulk_transfer_error(ret);
	return n;
}

int bulk_write(int endpoint, unsigned char *buf, int length) {
	int ret, n;
	if ((ret = libusb_bulk_transfer(device_handle, LIBUSB_ENDPOINT_OUT
			| endpoint, buf, length, &n, TIMEOUT)) < 0)
		bulk_transfer_error(ret);
	if (n)
		fprintf(stderr, "Sent %d bytes\n", n);
	return n;
}

int main(int argc, char **argv) {

	FILE *pFile = NULL;
	char * buffer;

	unsigned char buf[0x5000];
	unsigned char buf2[300];

	memset(buf2, 0, 300);
	int size;
	long lSize;

	pFile = fopen("blink.bin", "rb");

	// obtain file size:
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	// allocate memory to contain the whole file:
	 buffer = (char*) malloc (sizeof(char)*lSize);
	 if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

	 size = fread(buf, 1, lSize, pFile);
	 if (size != lSize) {fputs ("Reading error",stderr); exit (3);}


	libusb_context *context;
	libusb_init(&context);

	libusb_set_debug(context, 3);

	device_handle = libusb_open_device_with_vid_pid(context, VID, PID);
	if (!device_handle) {
		fprintf(stderr, "ERROR: Unable to find device "
			"(Vendor ID = %04x, Product ID = %04x)\n", VID, PID);
		return 1;
	}
	libusb_claim_interface(device_handle, 2);

	libusb_set_interface_alt_setting(device_handle, 0, 0);

	usleep(100);

	// Get the installes version
	GetVersion();
	GetVersion1();
	GetVersion2();

	char defout[] = { 0x00, 0x80, 0x04, 0x00, 0x2d, 0x10, 0x00, 0x00 };

	control_in_vendor_device(0x70, 0, 0, 5);

	usleep(100);

	control_out(0xfd, 0, 0x4f3, defout, 8);

	usleep(200);

	// Download the code

	bulk_write(3, buf, lSize);
	usleep(200);

	char defout2[] = { 0x00, 0x80, 0x04, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 };

	control_out(0xfd, 0, 0x4f1, defout2, 0x10);

	usleep(100);

	// Dont know
	bulk_write(3, buf2, 256);

	usleep(100);

	if (pFile)
		fclose(pFile);

	free (buffer);

	libusb_release_interface(device_handle, 0);
	libusb_close(device_handle);
	libusb_exit(context);
	return 0;
}
