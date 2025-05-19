#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct snode {
    char val;
    bool m;
    struct snode *f;
    struct snode *r;
} Tnode;

typedef Tnode* TTrie;

void ajouterMot(TTrie *trie , const char *mot) {
    if (*mot == '\0') {
        if (*trie) (*trie)->m = true;
        return;
    }

    TTrie *courant = trie;
    while (*courant && (*courant)->val < *mot) {
        courant = &((*courant)->r);
    }

    if (!*courant || (*courant)->val > *mot) {
        TTrie nouveau = (TTrie)malloc(sizeof(Tnode));
        nouveau->val = *mot;
        nouveau->m = false;
        nouveau->f = NULL;
        nouveau->r = *courant;
        *courant = nouveau;
    }

    ajouterMot(&((*courant)->f), mot + 1);

    if (*(mot + 1) == '\0') {
        (*courant)->m = true;
    }
}

void afficherTrie(TTrie trie, char *tab, int profondeur) {
    if (!trie) return;

    tab[profondeur] = trie->val;
    if (trie->m) {
        tab[profondeur + 1] = '\0';
        printf("%s\n", tab);
    }

    afficherTrie(trie->f, tab, profondeur + 1);
    afficherTrie(trie->r, tab, profondeur);
}

bool rechercherMot(TTrie trie, const char *mot) {
    if (!trie) return false;

    while (trie && trie->val < *mot) {
        trie = trie->r;
    }

    if (!trie || trie->val > *mot) {
        return false;
    }

    if (*(mot + 1) == '\0') {
        return trie->m;
    }

    return rechercherMot(trie->f, mot + 1);
}

int main() {
    TTrie monTrie = NULL;
    const char *mots[] = {"la", "ma", "me", "mai", "male", "mat", "mais", "main", "lait", "mal", NULL};
    const char *recherches[] = {"ma", "mat", "mal", "mauve", "main", "la", "m", NULL};

    for (int i = 0; mots[i] != NULL; i++) {
        ajouterMot(&monTrie, mots[i]);
    }

    char tab[100];
    printf("Contenu du Trie :\n");
    afficherTrie(monTrie, tab, 0);

    printf("\nTests de recherche :\n");
    for (int i = 0; recherches[i] != NULL; i++) {
        printf("%s : %s\n", recherches[i], rechercherMot(monTrie, recherches[i]) ? "trouvé" : "non trouvé");
    }

    return 0;
}
