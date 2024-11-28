#include <iostream>
#include <vector>
#include <limits> //std::numeric_limits +infty
#include <algorithm> // std::sort

#define min(a,b) (a<=b?a:b)
#define min4(a,b,c,d) (min(a,b)<=min(c,d)?min(a,b):min(c,d))

class Noeud {
    public:
        float valeur;
        Noeud* fils[5];
        int matrice[10];

        Noeud() : valeur(-1) {matrice[0]=-1; for (int i = 0; i < 5; ++i) {fils[i] = nullptr;}}
        Noeud(float val) : valeur(val) {matrice[0]=-1; for (int i = 0; i < 5; ++i) {fils[i] = nullptr;}}
        };

class Arbre {
public:
    Noeud racine;
    Arbre() {}
    Noeud* creerNoeud(float valeur) {return new Noeud(valeur);}
    Noeud* creerNoeud() {return new Noeud();}
    void printArbre(Noeud* noeud, int profondeur = 0) {
        if (!noeud) return;
        for (int i = 0; i < profondeur; ++i) 
            std::cout << "  "; 
        std::cout << "Noeud: valeur = " << noeud->valeur << " : ";
        if((noeud->matrice)[0]!=-1) std::cout <<"("<<noeud->matrice[0]<<", "<<noeud->matrice[1]<<", "<<noeud->matrice[2]<<", "<<noeud->matrice[3]<<", "<<noeud->matrice[4]<<", "<<noeud->matrice[5]<<", "<<noeud->matrice[6]<<", "<<noeud->matrice[7]<<", "<<noeud->matrice[8]<<", "<<noeud->matrice[9]<<")\n";
        else std::cout << "\n";
        for (int i = 0; i < 5; ++i) printArbre(noeud->fils[i], profondeur + 1);
    }
};





// Variables statiques
static Arbre arbre;
static bool hypothese = true;
static float p[4]; // pj de la colonne 1,2,3,4.





void checkHypothesis(float L1, float L2, float L3, float L4, 
                     float m1, float m2, float m3, float m4) {
    if(hypothese==false)return;
    float minL = min4(L1, L2, L3, L4);
    float minM = min4(m1, m2, m3, m4);
    if (not((L1==minL and m1==minM) or (L2==minL and m2==minM) or (L3==minL and m3==minM) or (L4==minL and m4==minM))){
        hypothese=false; 
        std::cout << "Liste des L :"<< L1 << " "<<L2 << " "<<L3 << " "<<L4 << "\n";
        std::cout << "Liste des M :"<< m1 << " "<<m2 << " "<<m3 << " "<<m4 << "\n";
        std::cout << std::endl;
    }
    // on va oublier si il y a des ex equo.
    
    /*std::vector<int> minIndicesL;
    if (L1 == minL) minIndicesL.push_back(1);
    if (L2 == minL) minIndicesL.push_back(2);
    if (L3 == minL) minIndicesL.push_back(3);
    if (L4 == minL) minIndicesL.push_back(4);
    std::vector<int> minIndicesM;
    if (m1 == minM) minIndicesM.push_back(1);
    if (m2 == minM) minIndicesM.push_back(2);
    if (m3 == minM) minIndicesM.push_back(3);
    if (m4 == minM) minIndicesM.push_back(4);
    std::sort(minIndicesL.begin(), minIndicesL.end());
    std::sort(minIndicesM.begin(), minIndicesM.end());

    if (minIndicesL.size() != minIndicesM.size()) {
        hypothese=false; 
        std::cout << "Liste des L :"<< L1 << " "<<L2 << " "<<L3 << " "<<L4 << "\n";
        std::cout << "Liste des M :"<< m1 << " "<<m2 << " "<<m3 << " "<<m4 << "\n";
        std::cout << std::endl;
        //for (int idx : minIndicesM) std::cout << idx << " ";
        //std::cout << std::endl;
    return;}
    for (size_t i = 0; i < minIndicesL.size(); ++i) {
        if (minIndicesL[i] != minIndicesM[i]) {hypothese=false;return;}
    }*/
}



    

// Fonction price
float price(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j) {
    Noeud* current = &arbre.racine;
    if (!current->fils[a])current->fils[a] = arbre.creerNoeud(); current = current->fils[a];
    if (!current->fils[b])current->fils[b] = arbre.creerNoeud(); current = current->fils[b];
    if (!current->fils[c])current->fils[c] = arbre.creerNoeud(); current = current->fils[c];
    if (!current->fils[d])current->fils[d] = arbre.creerNoeud(); current = current->fils[d];
    if (!current->fils[e])current->fils[e] = arbre.creerNoeud(); current = current->fils[e];
    if (!current->fils[f])current->fils[f] = arbre.creerNoeud(); current = current->fils[f];
    if (!current->fils[g])current->fils[g] = arbre.creerNoeud(); current = current->fils[g];
    if (!current->fils[h])current->fils[h] = arbre.creerNoeud(); current = current->fils[h];
    if (!current->fils[i])current->fils[i] = arbre.creerNoeud(); current = current->fils[i];
    if (!current->fils[j])current->fils[j] = arbre.creerNoeud(); current = current->fils[j];
    if(current->valeur!=-1) return current->valeur;
    float L1 = std::numeric_limits<float>::infinity();
    float L2 = std::numeric_limits<float>::infinity();
    float L3 = std::numeric_limits<float>::infinity();
    float L4 = std::numeric_limits<float>::infinity();
    
    if (a != 0) {L1 = 0 + price(a-1, b, c, d, e, f, g, h, i, j);}
    if ((b+c) != 0) {
        L2=0;
        if(b!=0) L2+=((1.0*b)/(b+c))*(0+ price(a, b-1, c, d, e, f, g, h, i, j));
        if(c!=0) L2+=((1.0*c)/(b+c))*((p[1]-p[0])*(a+b+d+g) + price(a, b, c-1, d, e, f, g, h, i, j));
        }
    if ((d+e+f)!= 0) {
        L3=0;
        if(d!=0) L3+=((1.0*d)/(d+e+f))*(0 + price(a, b, c, d-1, e, f, g, h, i, j));
        if(e!=0) L3+=((1.0*e)/(d+e+f))*((p[1]-p[0])*(a+b+d+g) + price(a, b, c, d, e-1, f, g, h, i, j));
        if(f!=0) L3+=((1.0*f)/(d+e+f))*((p[2]-p[0])*(a+b+d+g) + (p[2]-p[1])*(c+e+h) + price(a, b, c, d, e, f-1, g, h, i, j));
        }
    if ((g+h+i+j) != 0) {
        L4=0;
        if(g!=0) L4+=((1.0*g)/(g+h+i+j))*(0 + price(a, b, c, d, e, f, g-1, h, i, j));
        if(h!=0) L4+=((1.0*h)/(g+h+i+j))*((p[1]-p[0])*(a+b+d+g) + price(a, b, c, d, e, f, g, h-1, i, j));
        if(i!=0) L4+=((1.0*i)/(g+h+i+j))*((p[2]-p[0])*(a+b+d+g) + (p[2]-p[1])*(c+e+h) + price(a, b, c, d, e, f, g, h, i-1, j));        
        if(j!=0) L4+=((1.0*j)/(g+h+i+j))*((p[3]-p[0])*(a+b+d+g) + (p[3]-p[1])*(c+e+h) + (p[3]-p[2])*(f+i)+ price(a, b, c, d, e, f, g, h, i, j-1));
        }
    
    if(hypothese==true){
        float m1=std::numeric_limits<float>::infinity();
        float m2=std::numeric_limits<float>::infinity();
        float m3=std::numeric_limits<float>::infinity();
        float m4=std::numeric_limits<float>::infinity();
        if (a != 0) {m1 = p[0];}
        if (b+c != 0) {m2 = (1.0*(b*p[0]+c*p[1]))/(b+c);}
        if (d+e+f != 0) {m3 = (1.0*(d*p[0]+e*p[1]+f*p[2]))/(d+e+f);}
        if (g+h+i+j != 0) {m4 = (1.0*(g*p[0]+h*p[1]+i*p[2]+j*p[3]))/(g+h+i+j);}
        checkHypothesis(L1,L2,L3,L4,m1,m2,m3,m4);   
        if(hypothese==false){
            std::cout<<"instance : "<<a<<", "<<b<<", "<<c<<", "<<d<<", "
                            <<e<<", "<<f<<", "<<g<<", "<<h<<", "<<i<<", "<<j<<"\n";
        
        }     
    }
    float minL = min4(L1, L2, L3, L4);
    if(minL==std::numeric_limits<float>::infinity()) minL=0;
    current->valeur=minL;
    current->matrice[0]=a;
    current->matrice[1]=b;
    current->matrice[2]=c;
    current->matrice[3]=d;
    current->matrice[4]=e;
    current->matrice[5]=f;
    current->matrice[6]=g;
    current->matrice[7]=h;
    current->matrice[8]=i;
    current->matrice[9]=j;
    
    return minL;
}


    
    

int main() {
    // Exemple d'utilisation
    std::cout << "Initialisation de l'arbre.\n";
    p[0] = 1.1;
    p[1] = 3.01;
    p[2] = 5.001;
    p[3] = 6.0001;
    //float value = price(1, 2, 1, 1, 2, 2, 1, 0, 1, 0);
    float value = price(0, 0, 1, 1, 0, 1, 0, 0, 0, 0);
    //price(3, 3, 3, 3, 3, 3, 3, 3, 3, 3);
    //price(3, 3, 3, 3, 3, 3, 1, 3, 3, 3);

    //std::cout << "\nAffichage de l'arbre :\n";
    std::cout << "\nAffichage de la valeur :" << value << "\n";
        std::cout << "\nL'Hypothèse est :" << hypothese << "\n";
    //arbre.printArbre(&arbre.racine);
    
       return 0;
}
