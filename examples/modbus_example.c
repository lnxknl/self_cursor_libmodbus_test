/*
 * Simple Modbus example for reading and writing to a Modbus device
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus.h>

int main(int argc, char *argv[])
{
    modbus_t *ctx = NULL;
    uint16_t reg_write[1];
    uint16_t reg_read[10];
    uint8_t bits_write[1];
    uint8_t bits_read[10];
    int rc;
    int i;

    /* Create a new Modbus TCP connection */
    ctx = modbus_new_tcp("127.0.0.1", 502);  // Default Modbus TCP port is 502
//ctx = modbus_new_rtu("/dev/ttyUSB0", 115200, 'N', 8, 1);  // Adjust port and settings
    if (ctx == NULL) {
        fprintf(stderr, "Failed to create Modbus context: %s\n", modbus_strerror(errno));
        return -1;
    }

    /* Set the slave ID */
    modbus_set_slave(ctx, 1);

    /* Connect to the Modbus device */
    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }

    printf("Connected to Modbus device\n");

    /* Example 1: Write and read a single coil (digital output) */
    printf("\nExample 1: Writing and reading a coil\n");
    bits_write[0] = 1;  // Set coil to ON
    rc = modbus_write_bit(ctx, 0, bits_write[0]);
    if (rc != 1) {
        fprintf(stderr, "Failed to write coil: %s\n", modbus_strerror(errno));
    } else {
        printf("Written value %d to coil at address 0\n", bits_write[0]);
    }

    /* Read back the coil value */
    rc = modbus_read_bits(ctx, 0, 1, bits_read);
    if (rc != 1) {
        fprintf(stderr, "Failed to read coil: %s\n", modbus_strerror(errno));
    } else {
        printf("Read value %d from coil at address 0\n", bits_read[0]);
    }

    /* Example 2: Write and read multiple coils */
    printf("\nExample 2: Writing and reading multiple coils\n");
    bits_write[0] = 1;
    rc = modbus_write_bits(ctx, 0, 1, bits_write);
    if (rc != 1) {
        fprintf(stderr, "Failed to write coils: %s\n", modbus_strerror(errno));
    } else {
        printf("Written values to coils starting at address 0\n");
    }

    /* Read back multiple coils */
    rc = modbus_read_bits(ctx, 0, 5, bits_read);
    if (rc != 5) {
        fprintf(stderr, "Failed to read coils: %s\n", modbus_strerror(errno));
    } else {
        printf("Read values from coils starting at address 0:\n");
        for (i = 0; i < 5; i++) {
            printf("Coil %d: %d\n", i, bits_read[i]);
        }
    }

    /* Example 3: Write and read a single register (16-bit value) */
    printf("\nExample 3: Writing and reading a register\n");
    reg_write[0] = 12345;  // Example value
    rc = modbus_write_register(ctx, 0, reg_write[0]);
    if (rc != 1) {
        fprintf(stderr, "Failed to write register: %s\n", modbus_strerror(errno));
    } else {
        printf("Written value %d to register at address 0\n", reg_write[0]);
    }

    /* Read back the register value */
    rc = modbus_read_registers(ctx, 0, 1, reg_read);
    if (rc != 1) {
        fprintf(stderr, "Failed to read register: %s\n", modbus_strerror(errno));
    } else {
        printf("Read value %d from register at address 0\n", reg_read[0]);
    }

    /* Example 4: Write and read multiple registers */
    printf("\nExample 4: Writing and reading multiple registers\n");
    for (i = 0; i < 5; i++) {
        reg_write[0] = 1000 + i;
        rc = modbus_write_register(ctx, i, reg_write[0]);
        if (rc != 1) {
            fprintf(stderr, "Failed to write register %d: %s\n", i, modbus_strerror(errno));
        }
    }

    /* Read back multiple registers */
    rc = modbus_read_registers(ctx, 0, 5, reg_read);
    if (rc != 5) {
        fprintf(stderr, "Failed to read registers: %s\n", modbus_strerror(errno));
    } else {
        printf("Read values from registers starting at address 0:\n");
        for (i = 0; i < 5; i++) {
            printf("Register %d: %d\n", i, reg_read[i]);
        }
    }

    /* Example 5: Read input registers (read-only registers) */
    printf("\nExample 5: Reading input registers\n");
    rc = modbus_read_input_registers(ctx, 0, 5, reg_read);
    if (rc != 5) {
        fprintf(stderr, "Failed to read input registers: %s\n", modbus_strerror(errno));
    } else {
        printf("Read values from input registers starting at address 0:\n");
        for (i = 0; i < 5; i++) {
            printf("Input Register %d: %d\n", i, reg_read[i]);
        }
    }

    /* Close the connection and free the context */
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
} 