/* TODO: Make state persistent across multiple iterations of the main loop, so
 * we don't keep having to input VAS, PAS, VPN, PPN, etc. Perhaps have a global
 * struct VMSystem.
 * Refactor some code so we don't have so much repeating code: e.g. do we really
 * have to have the code for finding page offset /that/ many times? No way.
 * Organize variables within each switch case, make sure you're declaring them
 * in the right places and that unintended changes aren't bleeding into other
 * cases.
 * Add assert statements or error handling so we don't have unreasonable inputs
 * (e.g. VAS being smaller than VPN, negative inputs, etc)
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

char buf[256];
char *ptr;

void getinput(int *);
int findvpn(int, int, int);
int findppn(int, int, int);
int findoffset(int, int);

int main(void)
{
	int ans;
	int sizeVAS, sizeVPN, sizePAS, sizePPN, sizePTE;
	int offset, sizeVM, sizePM;

	printf("Note: this program takes input in terms of bits, NOT bytes/"
			"kilobytes/megabytes, etc.\n");
	printf("It only outputs Max PM and Max VM in terms of bytes.\n");
	printf("This program assumes you are given the basic info of the VM system "
			"(VAS, VPN, PAS, PPN)\n");
	
	while (true){
		printf("What are you trying to find? Enter the corresponding number in"
				" brackets:\n");
		printf("- Levels [1]\n- Level Indices [2]\n- Max PM [3]\n- Max VM [4]"
				"\n- Total # PTEs [5]\n- # PTEs per page [6]\n");
		
		getinput(&ans);

		switch (ans){
			case 1: // Find levels
				printf("You must supply either both VAS and VPN, or PAS and "
						"PPN. You must supply the PTE.\n\n");

				printf("Enter the size of the PAS: \n");
				getinput(&sizePAS);

				printf("Enter the size of the PPN: \n");
				getinput(&sizePPN);

				printf("Enter the size of the VAS: \n");
				getinput(&sizeVAS);

				printf("Enter the size of the VPN: \n");
				getinput(&sizeVPN);
				
				if (sizePAS && sizePPN)
					offset = findoffset(sizePAS, sizePPN);
				else if (sizeVAS && sizeVPN)
					offset = findoffset(sizeVAS, sizeVPN);
				else 
					fprintf(stderr, "You must supply either both VAS and VPN, "
							"or PAS and PPN.\n");

				if (!sizeVPN)
					sizeVPN = sizeVAS - offset;

				printf("Enter the size of the PTE: \n\n");
				getinput(&sizePTE);

				int pteSizeBytes = ceil((double)sizePTE / 8.);
				printf("PTE size in bytes = %d\n", pteSizeBytes);

				int logPgSize = ceil(log2(pteSizeBytes));
				printf("PTE size (bytes) in terms of 2^n = %d\n", logPgSize);

				int expNumPTE = offset - logPgSize;
				printf("# of PTEs in a table in terms of 2^n = %d\n", expNumPTE);
	
				int numLevels = ceil((double)sizeVPN/(double)expNumPTE);
				printf("Levels = ceil(size of VPN/# of PTES in terms of 2^n) "
						"= %d\n", numLevels);
					
				break;

			case 2: // Find level indices
				printf("Enter the size of the PAS: \n");
				getinput(&sizePAS);

				printf("Enter the size of the PPN: \n");
				getinput(&sizePPN);

				printf("Enter the size of the VAS: \n");
				getinput(&sizeVAS);

				printf("Enter the size of the VPN: \n");
				getinput(&sizeVPN);
				
				if (sizePAS && sizePPN)
					offset = findoffset(sizePAS, sizePPN);
				else if (sizeVAS && sizeVPN)
					offset = findoffset(sizeVAS, sizeVPN);
				else
					fprintf(stderr, "You must supply either both VAS and VPN, "
							"or PAS and PPN.\n");
				
				printf("Enter the size of the PTE: \n");
				getinput(&sizePTE);

				pteSizeBytes = ceil((double)sizePTE / 8.);
				int indices = offset - log2(pteSizeBytes);
				printf("Indices = %d\n", indices);
				break;
			
			case 3: // Find max PM
				printf("Enter the size of the PAS: \n");
				getinput(&sizePAS);
				
				if (sizePAS >= 40){
					int ones = sizePAS - 40;
					sizePM = pow(2., ones);
					printf("Max PM = %dTB\n", sizePM);
				} else if (sizePAS >= 30){
					int ones = sizePAS - 30;
					sizePM = pow(2., ones);
					printf("Max PM = %dGB\n", sizePM);
				} else if (sizePAS >= 20){
					int ones = sizePAS - 20;
					sizePM = pow(2., ones);
					printf("Max PM = %dMB\n", sizePM);
				} else if (sizePAS >= 10){
					int ones = sizePAS - 10;
					sizePM = pow(2., ones);
					printf("Max PM = %dKB\n", sizePM);
				}
				break;

			case 4: // Find max VM
					printf("Enter the size of the VAS: \n");
					getinput(&sizeVAS);
				if (sizeVAS >= 40){
					int ones = sizeVAS - 40;
					sizeVM = pow(2., ones);
					printf("Max VM = %dTB\n", sizeVM);
				} else if (sizeVAS >= 30){
					int ones = sizeVAS - 30;
					sizeVM = pow(2., ones);
					printf("Max VM = %dGB\n", sizeVM);
				} else if (sizeVAS >= 20){
					int ones = sizeVAS - 20;
					sizeVM = pow(2., ones);
					printf("Max VM = %dMB\n", sizeVM);
				} else if (sizeVAS >= 10){
					int ones = sizeVAS - 10;
					sizeVM = pow(2., ones);
					printf("Max VM = %dKB\n", sizeVM);
				}
				break;

			case 5: // Find total # PTEs
				printf("Enter the size of the PAS: \n");
				getinput(&sizePAS);

				printf("Enter the size of the PPN: \n");
				getinput(&sizePPN);

				printf("Enter the size of the VAS: \n");
				getinput(&sizeVAS);

				printf("Enter the size of the VPN: \n");
				getinput(&sizeVPN);
				
				if (sizePAS && sizePPN)
					offset = findoffset(sizePAS, sizePPN);
				else if (sizeVAS && sizeVPN)
					offset = findoffset(sizeVAS, sizeVPN);
				else
					fprintf(stderr, "You must supply either both VAS and VPN, "
							"or PAS and PPN.\n");

				if (!sizeVPN)
					sizeVPN = sizeVAS - offset;

				int totalNumPTE = pow(2, sizeVPN - offset);
				printf("# of PTEs = %d\n", totalNumPTE);
				break;

			case 6: // Find # PTEs per page
				printf("Enter the size of the PAS: \n");
				getinput(&sizePAS);

				printf("Enter the size of the PPN: \n");
				getinput(&sizePPN);

				printf("Enter the size of the VAS: \n");
				getinput(&sizeVAS);

				printf("Enter the size of the VPN: \n");
				getinput(&sizeVPN);
				
				if (sizePAS && sizePPN)
					offset = findoffset(sizePAS, sizePPN);
				else if (sizeVAS && sizeVPN)
					offset = findoffset(sizeVAS, sizeVPN);
				else
					fprintf(stderr, "You must supply either both VAS and VPN,"
							"or PAS and PPN.\n");

				printf("Enter the size of the PTE: \n");
				getinput(&sizePTE);

				pteSizeBytes = ceil((double)sizePTE / 8.);
				logPgSize = ceil(log2(pteSizeBytes));

				expNumPTE = offset - logPgSize;
				printf("PTEs per page = %.0f\n", pow(2, (expNumPTE + 1)));
				break;

			default:
				fprintf(stderr, "Not a valid answer. Must be in [1,7].\n");
				printf("Quit program? (y/n)\n");
				fgets(buf, sizeof(buf), stdin);
				if (buf[0] == 'y')
					exit(0);
				else continue;
		} 
		printf("Done! Quit program? (y/n)\n");
		fgets(buf, sizeof(buf), stdin);
		if (buf[0] == 'y')
			exit(0);
		else continue;
	}
	return 0;
}

void getinput(int *metric)
{
	if(fgets(buf, sizeof(buf), stdin) != NULL)
		*metric = strtod(buf, &ptr);
}

int findvpn(int VAS, int PAS, int PPN)
{
	int offset;
	if (PAS != 0)
		offset = PAS - PPN;
	else {
		fprintf(stderr, "You must input a non-zero PAS.\n");
		return -1;
	}
	if (!VAS){
		fprintf(stderr, "You must input a non-zero VAS.\n");
		return -1;
	}
	return VAS - offset;
}

int findoffset(int AS, int PN)
{
	return AS - PN;
}

int findppn(int VAS, int PAS, int VPN)
{
	int offset;
	if (PAS != 0)
		offset = VAS - VPN;
	else {
		fprintf(stderr, "You must input a non-zero PAS.\n");
		return -1;
	}
	if (!VAS){
		fprintf(stderr, "You must input a non-zero VAS.\n");
		return -1;
	}
	return PAS - offset;
}
