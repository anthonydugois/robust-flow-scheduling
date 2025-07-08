#include <iostream>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <memory>

using Ligne = std::vector<int>;
using Matrice = std::vector<Ligne*>;


struct NoeudMatrice {std::map<int, NoeudMatrice> enfants; std::vector<std::pair<Matrice, double>> matrices;};

static NoeudMatrice MATRICES;
std::vector<double> Pj;
static int nombreelemdansMATRICES=0;
static int nbr_matrices=0;
        
void trierMatrice(Matrice& m);
bool matricesEgales(const Matrice& a, const Matrice& b);
void ajouterDansMATRICES(const Matrice& m, double val);
bool estMatriceNulle(const Matrice& m);
Matrice soustraireUn(const Matrice& original, int i, int j);
double chercherValeurMatrice(const Matrice& m);
double calcul_a_faire(const Matrice& m, int j);
double calculer_optimal_value(const Matrice& m);
Matrice soustraireUn(const Matrice& original, int i, int j);
void instancierMATRICES(const Matrice& t);
void afficherLigneMatrice(const Matrice& m);
void afficherMATRICES(const NoeudMatrice& noeud, std::vector<int> prefixe = {});




void trierMatrice(Matrice& m) {
    std::sort(m.begin(), m.end(), [](const Ligne* a, const Ligne* b) {
        int A = std::accumulate(a->begin(), a->end(), 0);
        int B = std::accumulate(b->begin(), b->end(), 0);
        if (A != B) return A < B;
        return *a < *b;
    });
}

bool matricesEgales(const Matrice& a, const Matrice& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] == b[i]) continue; // Pointeurs identiques de lignes identiques
        if (*(a[i]) != *(b[i])) return false; // Sinon, comparer contenu
    }
    return true;
}




void ajouterDansMATRICES(const Matrice& m, double val) {
    NoeudMatrice* c = &MATRICES;
    for (const auto& l : m) {
        int s = std::accumulate(l->begin(), l->end(), 0);
        c = &c->enfants[s];
    }
    for (const auto& [mat, v] : c->matrices) {
        if (matricesEgales(mat, m)) return; // Déjà présente
    }
    c->matrices.emplace_back(m, val); // Nouvelle matrice
	/*std::cout << "Nouvelle matrice :  ";
    afficherLigneMatrice(m);
	std::cout << "Valeur associée :",val;*/
}

bool estMatriceNulle(const Matrice& m) {
    for (const auto& ligne : m)
        for (int val : *ligne)
            if (val != 0) return false;
    return true;
}



double chercherValeurMatrice(const Matrice& m) {
    NoeudMatrice* c = &MATRICES;
    for (const auto& l : m) {
        int s = std::accumulate(l->begin(), l->end(), 0);
        c = &c->enfants[s];
    }
    for (const auto& [mat, val] : c->matrices) {
        if (matricesEgales(mat, m)) return val;
    }
    return -1.0; // Non trouvée
}

double calcul_a_faire(const Matrice& m, int j) {
    double somme = 0.0;
    for (int k = 0; k < j; ++k) {
        int colonne_sum = 0;
        for (const auto& ligne : m) colonne_sum += (*ligne)[k];
        somme += colonne_sum * (Pj[j] - Pj[k]);
    }
    return somme;
}

double calculer_optimal_value(const Matrice& m) {
    double deja = chercherValeurMatrice(m);
    if (deja >= 0) return deja;
    if (estMatriceNulle(m)) return 0.0;

    std::vector<double> sumaverage(m.size(), 0.0);

	//bool une_ligne_traitee = false;//condition d'arret : si aucune ligne n'a été traitée, c'est que la matrice est decidable et son overcost est censé valoir 0.
    for (size_t i = 0; i < m.size(); ++i) {
        int somme_i = std::accumulate(m[i]->begin(), m[i]->end(), 0);
        if (somme_i == 0) continue;
		
		// ajouter conditions d'arret ici pour les matricces decidables
		

        for (size_t j = 0; j < m[i]->size(); ++j) {
            int val = (*m[i])[j];
            if (val == 0) continue;
            Matrice m2 = soustraireUn(m, i, j);
            double subval = calculer_optimal_value(m2);
            double extra = calcul_a_faire(m, j);
            sumaverage[i] += (val / static_cast<double>(somme_i)) * (subval + extra);
			une_ligne_traitee=true;
		}
    }
	if(une_ligne_traitee==false){ajouterDansMATRICES(m, 0); return 0;}

    double res = 1e9;
    for (size_t i = 0; i < m.size(); ++i) {
        if (std::accumulate(m[i]->begin(), m[i]->end(), 0) > 0)
            res = std::min(res, sumaverage[i]);
    }
    ajouterDansMATRICES(m, res);
    return res;
}

Matrice soustraireUn(const Matrice& original, int i, int j) {
    if ((*original[i])[j] == 0) return {};
    Matrice modifiee(original.size());
    for (size_t k = 0; k < original.size(); ++k) {
        if (k == i) {
            Ligne* nouvelle = new Ligne(*original[k]);
            (*nouvelle)[j] -= 1;
            modifiee[k] = nouvelle;
        } else {
            modifiee[k] = original[k];
        }
    }
    trierMatrice(modifiee);
    // calculer la valeur maintenant pour insertion dans MATRICES
    calculer_optimal_value(modifiee);
    return modifiee;
}

void instancierMATRICES(const Matrice& t) {
    NoeudMatrice* c = &MATRICES;
    for (const auto& l : t) {
        int s = std::accumulate(l->begin(), l->end(), 0);
        c = &c->enfants[s];
    }
    double val = calculer_optimal_value(t);

    c->matrices.emplace_back(t, val);
}
// Affichage compact d’une matrice (une ligne par ligne)
void afficherLigneMatrice(const Matrice& m) {
    for (const auto& ligne : m) {
        std::cout << "[";
        for (size_t i = 0; i < ligne->size(); ++i) {
            std::cout << (*ligne)[i];
            if (i + 1 < ligne->size()) std::cout << " ";
        }
        std::cout << "]";
    }
    std::cout << "\n";
}


// Affiche récursivement les matrices dans l’arbre
void afficherMATRICES(const NoeudMatrice& noeud, std::vector<int> prefixe) {
	if (!noeud.matrices.empty()) {
		std::cout << "MATRICES";
        for (int val : prefixe) std::cout << "[" << val << "]";
        std::cout << " contient " << noeud.matrices.size() << " matrice(s) :\n";
		nbr_matrices+=noeud.matrices.size();
        //for (const auto& [matrice, valeur] : noeud.matrices) {std::cout << "  Valeur associée : " << valeur << "\t \t => ";afficherLigneMatrice(matrice);}
    }

    for (const auto& [somme, enfant] : noeud.enfants) {
        auto nouveau_prefixe = prefixe;
        nouveau_prefixe.push_back(somme);
        afficherMATRICES(enfant, nouveau_prefixe);
    }
}



int main() {
    /*std::vector<Ligne> base = {
        {3, 3, 3, 1, 2},
        {3, 3, 3, 2, 1},
        {4, 4, 4, 1, 1},
        {8, 3, 6, 1, 1},
        {7, 7, 6, 1, 1}
    };
	// Initialiser Pj : par ex. {0, 1, 5, 10, 20}    
	for (int i = 0; i < 5; ++i) Pj.push_back(i == 0 ? 0 : Pj[i-1] + i);*/
	
   std::vector<Ligne> base = {
        {3, 3, 3,},
        {3, 3, 3},
        {3, 3, 3},
    };
	Pj.push_back(0);Pj.push_back(1);Pj.push_back(10);
  //std::vector<Ligne> base = {{0, 0, 0},{0, 1, 0},{1, 0, 1}}; Pj.push_back(1.1);Pj.push_back(3.01);Pj.push_back(5.001);

    Matrice triee;
    for (auto& l : base) triee.push_back(&l);
    trierMatrice(triee);


    instancierMATRICES(triee);
	std::cout << "\n\n______________________________________________\n\n"; 
	afficherMATRICES(MATRICES, {});
	
	
    std::cout << "Valeur optimale : " << calculer_optimal_value(triee) << std::endl;

	int produit_total = 1;for (const auto& ligne : base) {for (int val : ligne) {produit_total *= (val+1);}}
	std::cout << "Le nombre total de matrices dans MATRICES est : "<<nbr_matrices<<" au lieu de "<< produit_total << std::endl;

    return 0;
}
