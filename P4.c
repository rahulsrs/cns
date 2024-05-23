#include <stdio.h>
#include <math.h>

float en[3][1], de[3][1], a[3][3], b[3][3], msg[3][1];

void getKeyMatrix() {
    int i, j;

    printf("Enter 3x3 matrix for key (should have inverse):\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            scanf("%f", &a[i][j]);
        }
    }

    printf("\nEnter a string of 3 letters (use A through Z): ");
    char mes[3];
    scanf("%s", mes);

    for (i = 0; i < 3; i++) {
        msg[i][0] = mes[i] - 65;
    }
}

void encrypt() {
    int i, j, k;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++) {
            en[i][j] = 0; // Initialize en to 0 for proper addition
            for (k = 0; k < 3; k++) {
                en[i][j] += a[i][k] * msg[k][j];
            }
        }
    }

    printf("\nEncrypted string is: ");
    for (i = 0; i < 3; i++) {
        printf("%c", (char)fmod(fmod(en[i][0], 26.0), 26.0) + 65); // Double modulo for clarity
    }
    printf("\n");
}

void inversematrix() {
    int i, j, k;
    float p, q;

    // Initialize identity matrix (b)
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            b[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (k = 0; k < 3; k++) {
        for (i = 0; i < 3; i++) {
            if (i != k) {
                p = a[i][k];
                q = a[k][k];
                for (j = 0; j < 3; j++) {
                    a[i][j] = a[i][j] * q - p * a[k][j];
                    b[i][j] = b[i][j] * q - p * b[k][j];
                }
            }
        }

        // Check for divisibility by zero (singular matrix)
        if (fabs(a[k][k]) < 1e-9) {
            printf("Singular matrix: Inverse does not exist.\n");
            return;
        }
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            b[i][j] /= a[i][i]; // Division by diagonal element
        }
    }

    printf("\n\nInverse Matrix is:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%.2f ", b[i][j]); // Print with 2 decimal places
        }
        printf("\n");
    }
}

void decrypt() {
    inversematrix();

    int i, j, k;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++) {
            de[i][j] = 0; // Initialize de to 0 for proper addition
            for (k = 0; k < 3; k++) {
                de[i][j] += b[i][k] * en[k][j];
            }
        }
    }

    printf("\nDecrypted string is: ");
    for (i = 0; i < 3; i++) {
         printf("%c", (char)fmod(fmod(de[i][0], 26.0), 26.0) + 65); // Double modulo for clarity
    }
    printf("\n");
}

int main() {
    getKeyMatrix();
    encrypt();
    decrypt();
    return 0;
}
