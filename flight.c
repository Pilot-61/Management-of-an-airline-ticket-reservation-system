/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:22:02 by mes-salh          #+#    #+#             */
/*   Updated: 2024/05/07 11:30:16 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numVol;
    char dateDp[12];
    char dateAr[12];
    float tarif;
    char tmpD[12];
    char tmpA[12];
    char NomAvion[20];
    char VillDpt[20];
    char VillArv[20];
} Avion;


typedef struct NodeArber {
    Avion data;
    struct NodeArber *filsDrt;
    struct NodeArber *filsGch;
} NodeA;


NodeA *creerNodeA(Avion data) {
    NodeA *root;
    root = (NodeA*)malloc(sizeof(NodeA));
    if (root == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    root->data = data;
    root->filsDrt = NULL;
    root->filsGch = NULL;
    return root;
}


NodeA *insertVol(NodeA *root, Avion value) {
    if (root == NULL) {
        root = creerNodeA(value);
        return root;
    }
    if (strcmp(value.VillDpt, root->data.VillDpt) < 0) {
        root->filsGch = insertVol(root->filsGch, value);
    } else if (strcmp(value.VillDpt, root->data.VillDpt) > 0) {
        root->filsDrt = insertVol(root->filsDrt, value);
    } else {
        root->filsGch = insertVol(root->filsGch, value);
    }
    return root;
}


void rechercheVols(NodeA *root, char *VilleDprt, char *VilleArv, char *date) {
    if (root == NULL) {
        return;
    }
    if (strcmp(root->data.VillDpt, VilleDprt) == 0 && strcmp(root->data.VillArv, VilleArv) == 0 && strcmp(root->data.dateDp, date) == 0) {
        printf(" %d %s %s %.2f %s %s %s \n", root->data.numVol, root->data.dateDp, root->data.dateAr, root->data.tarif, root->data.tmpD, root->data.tmpA, root->data.NomAvion);
    }
    rechercheVols(root->filsGch, VilleDprt, VilleArv, date);
    rechercheVols(root->filsDrt, VilleDprt, VilleArv, date);
}


typedef struct Info {
    char Nom[20];
    char Prenom[20];
    char CIN[20];
    int numVol;
    int NumPass;
    int numResservation;
} info;


typedef struct NodeListe {
    info data;
    struct NodeListe *next;
} NodeL;


NodeL *NodeListe(info val) {
    NodeL *racin;
    racin = (NodeL*)malloc(sizeof(NodeL));
    if (racin == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    racin->data = val;
    racin->next = NULL;
    return racin;
}


int verifierVol(NodeA *root, int NumVol) {
    if (root == NULL) {
        return 0;
    }
    while (root != NULL) {
        if (root->data.numVol == NumVol) {
            return 1;
        }
        if (root->data.numVol > NumVol) {
            root = root->filsGch;
        } else {
            root = root->filsDrt;
        }
    }
    return 0;
}

void Reserver_Billet(NodeL **liste, NodeA *root, info passager) {
    int numVol = passager.numVol;
    int vol = verifierVol(root, numVol);
    if (vol == 0) {
        printf("Le numero de vol est invalide.\n");
        return;
    }
    NodeL *nouvelleReservation = NodeListe(passager);
    if (*liste == NULL) {
        *liste = nouvelleReservation;
    } else {
        NodeL *courant = *liste;
        while (courant->next != NULL) {
            courant = courant->next;
        }
        courant->next = nouvelleReservation;
    }
    printf("La reservation a ete effectuee avec succes.\n");
}

void AnnulerRsrv(NodeL **liste, int NumRs) {
    if (*liste == NULL) {
        printf("La liste est vide.\n");
        return;
    }
    if ((*liste)->data.numResservation == NumRs) {
        NodeL *temp = *liste;
        *liste = (*liste)->next;
        free(temp);
        printf("Reservation supprimee.\n");
        return;
    }
    NodeL *courant = *liste;
    while (courant->next != NULL) {
        if (courant->next->data.numResservation == NumRs) {
            NodeL *temp = courant->next;
            courant->next = courant->next->next;
            free(temp);
            printf("Reservation supprimee.\n");
            return;
        }
        courant = courant->next;
    }
    printf("Numero de reservation invalide.\n");
}

void AfficherVol(NodeL *racin) {
    if (racin == NULL) {
        printf("Aucun vol reserve a afficher.\n");
    } else {
        printf("NumVol Nom Prenom CIN NumPass NumReservation\n");
        NodeL *temp = racin;
        while (temp != NULL) {
            printf(" %d %s %s %s %d %d\n", temp->data.numVol, temp->data.Nom, temp->data.Prenom, temp->data.CIN, temp->data.NumPass, temp->data.numResservation);
            temp = temp->next;
        }
    }
}

NodeL *rechercherPassager(NodeL *racine, char *CIN) {
    NodeL *courant = racine;
    while (courant != NULL) {
        if (strcmp(courant->data.CIN, CIN) == 0) {
            return courant;
        }
        courant = courant->next;
    }
    return NULL;
}

void modifierInfoPassager(NodeL *racine) {
    char CIN[20];
    printf("Entrez le CIN du passager pour modifier ses informations (ou 'quit' pour quitter): ");
    scanf("%s", CIN);

    if (strcmp(CIN, "quit") == 0) {
        return;
    }

    NodeL *passager = rechercherPassager(racine, CIN);
    if (passager == NULL) {
        printf("Passager non trouve.\n");
        return;
    }

    printf("Nouveau nom: ");
    scanf("%s", passager->data.Nom);
    printf("Nouveau prenom: ");
    scanf("%s", passager->data.Prenom);
    printf("Nouveau CIN: ");
    scanf("%s", passager->data.CIN);
    printf("Nouveau Numvol: ");
    scanf("%d", &passager->data.numVol);
    printf("Nouveau numero de passeport: ");
    scanf("%d", &passager->data.NumPass);
    printf("Informations mises a jour avec succes.\n");

    modifierInfoPassager(racine);
}


NodeA *root = NULL;
NodeL *racin = NULL;

char VillD[20], VillA[20], date[12];
int NumRs;

void menu();

int main(int argc, char *argv[]) {
    Avion vol1 = {1, "01/01/2022", "01/01/2022", 150.0, "10h00", "12h00", "Airbus A320", "Paris", "Londres"};
    Avion vol2 = {2, "01/02/2022", "01/02/2022", 200.0, "14h00", "16h30", "Boeing 747", "Londres", "New York"};
    Avion vol3 = {3, "01/01/2022", "01/03/2022", 250.0, "08h00", "12h00", "Airbus A380", "Paris", "Londres"};
    Avion vol4 = {4, "01/04/2022", "01/04/2022", 180.0, "09h00", "11h00", "Boeing 737", "Londres", "Madrid"};
    Avion vol5 = {5, "01/01/2022", "01/01/2023", 500.0, "10h00", "12h00", "Boeing 747", "TOKYO", "Londres"};
    Avion vol6 = {6, "01/01/2023", "02/01/2023", 600.0, "14h00", "16h00", "Airbus A380", "New York", "Paris"};
    Avion vol7 = {7, "01/01/2023", "02/01/2023", 700.0, "18h00", "20h00", "Boeing 737", "Madrid", "New York"};

    root = insertVol(root, vol1);
    root = insertVol(root, vol2);
    root = insertVol(root, vol3);
    root = insertVol(root, vol4);
    root = insertVol(root, vol5);
    root = insertVol(root, vol6);
    root = insertVol(root, vol7);

    menu();

    return 0;
}


void menu() {
    int choix;
    printf("1. Recherche de vols \n");
    printf("2. Reservation de billets\n");
    printf("3. Annulation de reservation\n");
    printf("4. Affichage des vols reserves\n");
    printf("5. Gestion des informations des passagers\n");
    printf("6. Quitter le programme\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choix);

    switch (choix) {
        case 1: {
            printf("Entrez la ville de depart: ");
            scanf("%s", VillD);
            printf("Entrez la ville d'arrivee: ");
            scanf("%s", VillA);
            printf("Entrez la date de depart (JJ/MM/AAAA): ");
            scanf("%s", date);
            printf("\n");
            printf("NumVol DateDepart DateArrivee Tarif HeureDepart HeureArrivee Avion\n");
            rechercheVols(root, VillD, VillA, date);
            printf("\n");
            menu();
            break;
        }
        case 2: {
            info passager;
            printf("Entrez votre Nom: ");
            scanf("%s", passager.Nom);
            printf("Entrez votre prenom: ");
            scanf("%s", passager.Prenom);
            printf("Entrez votre CIN: ");
            scanf("%s", passager.CIN);
            printf("Entrez votre Numvol: ");
            scanf("%d", &passager.numVol);
            printf("Entrez votre numero de passeport: ");
            scanf("%d", &passager.NumPass);
            printf("Entrez votre numero de reservation: ");
            scanf("%d", &passager.numResservation);
            Reserver_Billet(&racin, root, passager);
            printf("\n");
            menu();
            break;
        }
        case 3: {
            printf("Entrez le numero de reservation que vous souhaitez annuler: ");
            scanf("%d", &NumRs);
            AnnulerRsrv(&racin, NumRs);
            printf("\n");
            menu();
            break;
        }
        case 4: {
            printf("\n");
            AfficherVol(racin);
            printf("\n");
            menu();
            break;
        }
        case 5: {
        modifierInfoPassager(racin);
        printf("\n");
        menu();
        break;
        }

        case 6: {
            exit(0);
            break;
        }
        default: {
            printf("Verifier votre choix.\n");
            menu();
            break;
        }
    }
}
