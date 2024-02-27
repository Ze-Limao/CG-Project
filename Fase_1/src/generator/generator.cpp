#include "../utils/figura.hpp"
#include "../utils/ponto.hpp"
#include <string.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

//Função que gera o plano XZ	
Figura generatePlaneXZ(int length, int divisions, float h = 0.0f, int bottom = 0){
	Figura chaoDaCozinha = newEmptyFigura();
	if (chaoDaCozinha) {
		float larguraTotal = (float)length / 2,
			larguraAzulejo = (float)length / divisions,
			x1 = -larguraTotal, z1 = -larguraTotal,
			x2 = -larguraTotal, z2 = -larguraTotal + larguraAzulejo,
			x3 = -larguraTotal + larguraAzulejo, z3 = -larguraTotal,
			x4 = -larguraTotal + larguraAzulejo, z4 = -larguraTotal + larguraAzulejo;

		float arrX[4] = { x1, x2, x3, x4 };
		float arrZ[4] = { z1, z2, z3, z4 };

		if(bottom){
			arrX[1] = x3;
			arrX[2] = x2;
			arrZ[1] = z3;
			arrZ[2] = z2;
		}

		for (int linha = 0; linha < divisions; linha++) {
			for (int coluna = 0; coluna < divisions; coluna++) {
				// Primeiro triângulo do quadrado
				addPonto(chaoDaCozinha, newPonto(arrX[0] + coluna * larguraAzulejo, h, arrZ[0]));
				addPonto(chaoDaCozinha, newPonto(arrX[1] + coluna * larguraAzulejo, h, arrZ[1]));
				addPonto(chaoDaCozinha, newPonto(arrX[2] + coluna * larguraAzulejo, h, arrZ[2]));
				// Segundo triângulo do quadrado
				addPonto(chaoDaCozinha, newPonto(arrX[1] + coluna * larguraAzulejo, h, arrZ[1]));
				addPonto(chaoDaCozinha, newPonto(arrX[3] + coluna * larguraAzulejo, h, arrZ[3]));
				addPonto(chaoDaCozinha, newPonto(arrX[2] + coluna * larguraAzulejo, h, arrZ[2]));
			}
			arrZ[0] += larguraAzulejo;arrZ[1] += larguraAzulejo;arrZ[2] += larguraAzulejo;arrZ[3] += larguraAzulejo;
		}
	}

	return chaoDaCozinha;
}

int main(int argc, char* argv[]) {
    if (argc >= 5) {
        Figura figura;
        const char* file_path;
        if (strcmp(argv[1], "plane") == 0) {
            int length = atoi(argv[2]), divisions = atoi(argv[3]);
            file_path = argv[4];

            figura = generatePlaneXZ(length, divisions);
        }
        else if (strcmp(argv[1], "box") == 0) {
            int length = atoi(argv[2]), divisions = atoi(argv[3]);
            file_path = argv[4];

            //figura = generateBox(length, divisions);
        }
        else if (strcmp(argv[1], "sphere") == 0) {
            int radius = atoi(argv[2]), slices = atoi(argv[3]), stacks = atoi(argv[4]);
            file_path = argv[5];

            //figura = generateSphere(radius, slices, stacks);
        }
        else if (strcmp(argv[1], "cone") == 0) {
            int radius = atoi(argv[2]), height = atoi(argv[3]), slices = atoi(argv[4]), stacks = atoi(argv[5]);
            file_path = argv[6];

            //figura = generateCone(radius, height, slices, stacks);
        }
        else {
            printf("Figura inválida\n");
            return 1;
        }
        figuraToFile(figura, file_path);
        deleteFigura(figura);
    }
    else {
        printf("Número de argumentos inválido.\n");
        return 1;
    }
    return 0;
}