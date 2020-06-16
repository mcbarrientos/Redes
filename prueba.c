#include <stdio.h>
#include <stdlib.h>
#include <math.h>  
	
int main(int argc, char *argv[]) {

	int ip[4];			// Direccion IP
	int mask[4];	    // Mascara de sub red
	int net[4];			// Direccion de red	
	int broadcast[4];   // Direccion de broadcast
	int Bit_red, bits, Bit_Host;  
	int Cant_IPs, Cant_Host;
	int i, j, k;	
	char p;	

 
	printf("\nDigite su direcciòn IP: ");
	scanf("%d %c %d %c %d %c %d", &ip[0], &p, &ip[1], &p, &ip[2], &p, &ip[3]);
		
	Mascara_Entrada:
	printf("\nDigite su máscara de sub red: \n");
	scanf("%d %c %d %c %d %c %d", &mask[0], &p, &mask[1], &p, &mask[2], &p, &mask[3]);

	for (i=3; i>=0; --i) {
		if (mask[i]==0  || mask[i]==128 || mask[i]==192 || mask[i]==224 || mask[i]==240 || mask[i]==248 || mask[i]==252 || mask[i]==254 || mask[i]==255) {
			i++;
			i--;
		}  
		else {
			printf("\nSe ha digitado un valor incorrecto de máscara de red, los valores correctos son: 0 | 128 | 192 | 224 | 240 | 248 | 252 | 254 | 255\n");
			i = 3;  
			goto Mascara_Entrada;
		}
	}  
	for (i=3 ; i>=0 ; i--) {
		net[i] = ip[i] & mask[i];	
	}
	Bit_red = 0;
	for (i = 3; i>=0 ; i--) {
		j = mask[i];
		if (j > 1) { 
			bits = 128;
				while ( j > bits ) {
					Bit_red += 1;
					j -= bits;
					bits -= bits/2;
				}   
			Bit_red += 1;		
		}  
	}
	Bit_Host = 32 - Bit_red;	
	Cant_Host = (pow(2,Bit_Host)) - 2;

	while (k>8) {
		Cant_IPs += 256;	
		k -= 8;
	} 
	if (k<=8 && k > 0) {
		Cant_IPs += (pow(2,k)) - 1;
	} 
	for (i=3 ; i>= 0 ; i--) {
		if (mask[i] < 255) {
			j = 255 - mask[i];
			broadcast[i] = net[i] + j;
		} 
		if (mask[i]==255) {
			broadcast[i] = net[i];
		}  
		if (mask[i]==0) {
			broadcast[i] = 255;
		} 
	} 
	
	printf("Cantidad de host(2n-2): %d \n", Cant_Host);
	printf("Dirección de Red: %d %c %d %c %d %c %d\n", net[0], p, net[1], p, net[2], p, net[3]);
	printf("Primer dirección IP disponible: %d%c%d%c%d%c%d\n", net[0], p, net[1],  p, net[2], p, (net[3] + 1) );
	printf("Última dirección IP disponible: %d%c%d%c%d%c%d\n", broadcast[0], p, broadcast[1],  p, broadcast[2], p, broadcast[3] -1 );
	printf("Dirección de broadcast de la red: %d%c%d%c%d%c%d \n", broadcast[0], p, broadcast[1],  p, broadcast[2], p, broadcast[3] );
	printf("Gateway red: %d%c%d%c%d%c%d \n", broadcast[0], p, broadcast[1],  p, broadcast[2], p, broadcast[3] - 254 );

	return 0;

}