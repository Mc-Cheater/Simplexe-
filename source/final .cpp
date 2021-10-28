#include<stdio.h>
#include<stdlib.h>
#include<math.h>



//------------------------------Definitions des structures utilisées et de construire co facteur-------------------------------------------------------------------------------------------


typedef struct mat{
	float mult;
	float** mat;
	int taille;
	int n;
	int m;
}Matrice;
typedef Matrice* Element;
typedef struct sys{
	Matrice A;
	int * vect_col_base;
	int * vect_col_hb;
	float * Ct;
	float* Bt;
	float* Ct_b;
	float* Ct_hb;
	float z;
}Systeme_lineaire;
typedef struct cellule{
	Element e;
	struct cellule * suivant;
}Cellule;
typedef Cellule * Pile;

float ** construire_co_facteur(float **matrice,int del_line,int del_col,int n,int m,float **co_fac){
	for(int i=0 ;i <n;i++){
		for(int j=0;j<m;j++){
		if (i<del_line && j<del_col)
		co_fac[i][j]=matrice[i][j];
		else
		if(i<del_line && j> del_col)
		co_fac[i][j-1]=matrice[i][j];
		else 
		if(i>del_line && j<del_col)
		co_fac[i-1][j]=matrice[i][j];
		else 
		if(i>del_line && j>del_col)
		co_fac[i-1][j-1]=matrice[i][j];
	}
	}
//p.empiler(p,co_fac,n-1,m-1,matrice[del_line][del_col]);
return co_fac;
}
int est_vide(Pile p){
	return p==NULL;
	
}
Pile pile_vide(){
	return NULL;
	
}
Pile empiler(Pile p , Element e){
	
	Pile q=(Pile)malloc(sizeof(Cellule));
	q->e=e;
	q->suivant=p;
	p=q;
	return p;
	
	
	
	
}
Pile depiler(Pile p){
	if(est_vide(p))printf("erreur desempilage impossible car pile vide");
	else
	{Pile q=p;
p=p->suivant;
free(q);

return p;
		
		
	}
}
Element sommet(Pile p){
	if(est_vide(p))printf("erreur somme nexiste pas car pile vide");
	else
		return p->e;
	
}

// ----------------------------des fonctions utiles mult multiplier copier etc... ----------------------------------------------------------------


void echanger(float* a,float* b){
	
	float temp=*a;
	*a=*b;
	*b=temp;
	
	
}

void copier(float **mat ,int n,int m,float** copie){
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++){
//	printf("un element sera copie");
	copie[i][j]=mat[i][j];
}
	
	
}
void multiplier(float ** mat1,float ** mat2 ,int n,int m,int k,float** mat_result){
	float somme;
	for(int i=0;i<n;i++){
		
		for(int j=0;j<k;j++){
		somme=0.0;
		for(int z=0;z<m;z++)
		somme+=mat1[i][z]*mat2[z][j];
		mat_result[i][j]=somme;
	}}
	
	
	
	
	
}
void mult(float** mat,int n,int m,float scalaire){
	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)
	mat[i][j]*=scalaire;
	}
}
void construire_co_matrice(float** mat,int n/*,int del_line,int del_colonne*/,float *** comatrice_uncalculed,float ** co_fac){
for(int i=0;i<n;i++){
	
	for(int j=0;j<n;j++){
	//	printf("debut");
//		getchar();
		construire_co_facteur(mat,i,j,n,n,co_fac);
	//	getchar();
	//	printf("putin");
	//	getchar();
		copier(co_fac,n-1,n-1,comatrice_uncalculed[i*n+j]);
	//	printf("une construction de co_facteur a eu lieu ainsi qu'une copie en comatrice");
		//getchar();
		
		
	}
	
	
	
}}




















void det(Pile p,Pile q,float *somme){
	while(sommet(p)->taille>2){
	while(!est_vide(p)){
		for(int i=0;i<sommet(p)->taille;i++){
			Matrice* truc=(Matrice*)malloc(sizeof(Matrice));
			truc->taille=sommet(p)->taille-1;
			truc->mat=(float**)malloc((sommet(p)->taille-1)*sizeof(float*));
			for (int k=0;k<sommet(p)->taille-1;k++)
				truc->mat[k]=(float*)malloc((sommet(p)->taille-1)*sizeof(float));
			truc->mat=construire_co_facteur(sommet(p)->mat,0,i,sommet(p)->taille,sommet(p)->taille,truc->mat);
			truc->mult=pow(-1,i+2)*sommet(p)->mult*sommet(p)->mat[0][i];
			q=empiler(q,truc);
			
		}
		p=depiler(p);
		
		
		
	}
	//echanger(p,q);
	//Pile temp=p;
	p=q;
	//q=temp;
	
	q=pile_vide();
	}
	while(!est_vide(p)){printf("on est la");
		*somme+=sommet(p)->mult*(sommet(p)->mat[0][0]*sommet(p)->mat[1][1]-sommet(p)->mat[0][1]*sommet(p)->mat[1][0]);
		p=depiler(p);
	}
	
} 

void choix_base(float ** matrice,int n ,int m ,float ** base ,int mode,int* vect_base){
	
	int x=0;
	if(mode==0){printf("choisisser une base en entrant les indices des vecteurs colonne choisies\n");
	for(int i=0;i<((n<m)?n:m);i++){
														
	
	printf("entrez un veteur \n");
	fflush(stdin);
	scanf("%d",&x);
	vect_base[i]=x;
	for(int k=0;k<((n<m)?n:m);k++){
//	printf("k=%d et x=%d et i=%d",k,x,i);
//	getchar();
	fflush(stdin);
	base[k][i]=matrice[k][x];
	
	}}}
	else {
		
		
		
		
		
	}
	
	
	
	
}
void transposer(float** mat,int n){
	for(int i=0;i<n;i++)
	for(int j=0;j<i;j++)
	echanger(&mat[i][j],&mat[j][i]);
}
construire_sous_matrice(float ** mat,int n,int m,int nombre,int* vect,float** mat_ext,int mode){
	if(mode){
		for(int i=0;i<n;i++){
			for(int j=0;j<nombre;j++)
			mat_ext[i][j]=mat[i][vect[j]];
			
			
			
		}
		
		
		
		
		
		
		
		
		
		
	}
	
	
	
	
	
	
}






// vérification de l'optimalité de la solution avec cT comme paramétre 
int est_positif(float * vect,int taille){
	for(int i=0;i<taille;i++)
	if(vect[i]<0 )return 0;
	return 1;
}
int contain(int* vect,int element,int taille){
	for(int i=0;i<taille;i++){
	
if(vect[i]==element)
return 1;
}
return 0;


}


void vect_addition(float* v1,float* v2,int n,int boolean_soustraction,float* v_resultat){
for(int i=0;i<n;i++)
if(boolean_soustraction<=0)
v_resultat[i]=v1[i]+v2[i];
else 
v_resultat[i]=v1[i]-v2[i];
}












//--------------- le coeur du travail simplexe + B&B --------------------------------------------------------------------

void Simplexe(Systeme_lineaire sys,Systeme_lineaire ** trace/*float** mat,float * ct,float *bt*/){
int ite=0;
trace[0][ite]=sys;

float ***co_mat_Base=(float***)malloc(pow(sys.A.taille,2)*sizeof(float**));
	for(int i=0;i<pow(sys.A.taille,2);i++){
	
	co_mat_Base[i]=(float**)malloc((sys.A.taille-1)*sizeof(float*));
	for(int j=0;j<(sys.A.taille-1);j++)
	co_mat_Base[i][j]=(float*)malloc((sys.A.taille-1)*sizeof(float));
}

float** co_facteur=(float **)malloc((sys.A.taille-1)*sizeof(float*));
for(int i=0;i<sys.A.taille-1;i++)
co_facteur[i]=(float*)malloc((sys.A.taille-1)*sizeof(float));

	
float** matrice_base_A=(float**)malloc(sys.A.taille*sizeof(float*));
for(int i=0;i<sys.A.taille;i++)
matrice_base_A[i]=(float*)malloc(sys.A.taille*sizeof(float));

float** matrice_inverse_base_A=(float**)malloc(sys.A.taille*sizeof(float*));
for(int i=0;i<sys.A.taille;i++)
matrice_inverse_base_A[i]=(float*)malloc(sys.A.taille*sizeof(float));	

Systeme_lineaire tab_final;

float **cible_mult=(float**)malloc(sys.A.n*sizeof(float*));
for(int i=0;i<sys.A.n;i++)
cible_mult[i]=(float*)malloc(sys.A.m*sizeof(float));

float ** bi_cible=(float**)malloc(sizeof(float**));
bi_cible[0]=(float*)malloc(sys.A.taille*sizeof(float));

float ** z_barre=(float**)malloc(sizeof(float**));
z_barre[0]=(float*)malloc(sizeof(float));


int rest=((sys.A.m>sys.A.n)?sys.A.m:sys.A.n)-sys.A.taille;
float ** Reste=(float**)malloc(sys.A.taille*sizeof(float*));
for(int i=0;i<sys.A.taille;i++)
Reste[i]=(float*)malloc(sizeof(float)*rest);


tab_final.Ct=(float*)malloc(sys.A.taille*sizeof(float));
tab_final.Ct[0]=-1;
printf("la matrice associee au systeme lineaire est \n");

for(int i=0;i<sys.A.n;i++){
	for(int j=0;j<sys.A.m;j++)
	printf("%f\t",sys.A.mat[i][j]);
printf("\n");
}

choix_base(sys.A.mat,sys.A.n,sys.A.m,matrice_base_A,0,sys.vect_col_base);
printf("la base choisie est :\n");
for(int i=0;i<sys.A.taille;i++)
{for(int j=0;j<sys.A.taille;j++)
printf("%f\t",matrice_base_A[i][j]);
printf("\n");
}











	
	
	while(!est_positif(tab_final.Ct,sys.A.n)){
	//les variables oubliées
	Pile p=pile_vide();
	Element e=(Element)malloc(sizeof(Matrice));
	e->taille=sys.A.taille;
	e->mat=matrice_base_A;
	e->mult=1;
	p=empiler(p,e);
	Pile q=pile_vide();
	float *dete=(float*)malloc(sizeof(float));
	*dete=0;
	
	
	ite++;
	if(ite>1){
	
	//choix de la variable a entrez /sortir
}
	construire_co_matrice(matrice_base_A,sys.A.taille,co_mat_Base,co_facteur);
	printf("wtf-1");
	det(p,q,dete);
	printf("wtf0");
	for(int i=0;i<sys.A.taille;i++)
	{for(int j=0;j<sys.A.taille;j++){
	
	
	p=NULL;q=NULL;float* det_co=(float*)malloc(sizeof(float));
	*det_co=0;
	Matrice* util=(Element)malloc(sizeof(Matrice));
	util->taille=sys.A.taille-1;
	util->mult=pow(-1,i+j);
	util->mat=co_mat_Base[i*sys.A.taille+j];
	p=empiler(p,util);
	printf("wtf1");
	det(p,q,det_co);
	printf("wtf2");
	matrice_inverse_base_A[i][j]=*det_co/(*dete);
	printf("wtf3");
	}}
	transposer(matrice_inverse_base_A,sys.A.taille);
	multiplier(matrice_inverse_base_A,sys.A.mat,sys.A.n,sys.A.m,sys.A.m,cible_mult);
	multiplier(matrice_inverse_base_A,&sys.Bt,sys.A.taille,sys.A.taille,1,bi_cible);
	printf("wtf4");
	// besoin du R a construire
	int compteur=0;
	for(int i=0;i<((sys.A.m>sys.A.n)?sys.A.m:sys.A.n);i++){
		if(!contain(sys.vect_col_base,i,sys.A.taille))
		sys.vect_col_hb[compteur++]=i;
	}
	int j=0;
	int k=0;
	for(int i=0;i<((sys.A.m>sys.A.n)?sys.A.m:sys.A.n);i++){
		if(contain(sys.vect_col_base,i,sys.A.taille))
		sys.Ct_b[j++]=sys.Ct[i];
		else 
		if(contain(sys.vect_col_hb,i,((sys.A.m>sys.A.n)?sys.A.m:sys.A.n)-sys.A.taille))
			sys.Ct_hb[k++]=sys.Ct[i];
	}
	multiplier(&sys.Ct_b,bi_cible,sys.A.taille,sys.A.taille,1,z_barre);
	printf("wtf5");
	
	construire_sous_matrice(sys.A.mat,sys.A.n,sys.A.m,rest,sys.vect_col_hb,Reste,1);
	
	
	
	
	
	
	
	
	
	
	
	
	// le coeur du travail se fera ici l'iteration de simplexe avec tous ses calculs sont effectués ici
	// risible 1000 ligne de codes de préparation de fonctions et d'allocation memoire pour 20 lignes de code d'utilisation
	// vraiment le code le plus dur que j'ai eu a écrire
	//verifier que mult fonctionne pour nbcol==1
	//et aprés ce sera enfin fini de ce putain de code de merde de $ù*$m**$*ù$^$*$*^$
	//enfin il restera quand meme le branch and bound
	printf("wtf6");
	//calcul de bbarre cTbarre et zbarre
	tab_final.A.mat=cible_mult;
	tab_final.A.n=sys.A.n;
	tab_final.A.m=sys.A.m;
	tab_final.A.taille=sys.A.taille;
	sys.A.mult=1;
	tab_final.Bt=*bi_cible;
	tab_final.Ct=NULL;
	tab_final.Ct_b=NULL;
	tab_final.vect_col_base=NULL;
	tab_final.vect_col_hb=NULL;
	tab_final.z=**z_barre;
	trace[0]=(Systeme_lineaire*)realloc(trace[0],(ite+1)*sizeof(Systeme_lineaire));
	trace[0][ite]=sys;
	printf("\n debut de résultat d une putain d iteration\n");
	for(int i=0;i<tab_final.A.n;i++)
	{	for(int j=0;j<tab_final.A.m;j++)
			printf("%f\t",tab_final.A.mat[i][j]);
			printf("\n");
	}	
	printf("wtf7");
	getchar();getchar();getchar();
	
	
	
}



	
}












//------------------ le main -----------------------------

// -----------input du systeme lineaire initial dans le main-----------------------------------------------------




main(){
	int nombre_var;
int nombre_contraintes;


printf("entrez le nombre de variables puis le nombre de contraintes\n");
fflush(stdin);
scanf("%d",&nombre_var);
fflush(stdin);
scanf("%d",&nombre_contraintes);

float* ci=(float*)malloc(nombre_var*sizeof(float));
float** matrice_A=(float**)malloc(nombre_contraintes*sizeof(float*));
for(int i=0;i<nombre_contraintes;i++)
matrice_A[i]=(float*)malloc(nombre_var*sizeof(float));


int min =(nombre_var<nombre_contraintes)?nombre_var:nombre_contraintes;
float* bi=(float*)malloc(min*sizeof(float));

printf("entrez les valeurs des coefficient associes au var dans la fonction objectif inserer des 0 pour les variables absentes (exemple les variables d ecart)\n");
for(int i=0;i<nombre_var;i++)
{printf("entrez le coeffcient de la variable x%d\n",i);
fflush(stdin);
scanf("%f",ci+i);


}



for(int i=0;i<nombre_contraintes;i++){

for(int j=0;j<nombre_var;j++) {

printf("entrez l element a la case [%d] [%d]\n",i,j);
fflush(stdin);
scanf("%f",&matrice_A[i][j]);
}}

printf("entrez les valeurs des termes droit   \n");
for(int i=0;i<min;i++)
{printf("entrez le b%d\n",i);
fflush(stdin);
scanf("%f",bi+i);


}




Matrice sys;
sys.mat=matrice_A;
sys.mult=1;
sys.taille=min;
sys.n=nombre_contraintes;
sys.m=nombre_var;
Systeme_lineaire s;


s.A=sys;
s.Bt=bi;
s.Ct=ci;
s.vect_col_base=(int*)malloc(min*sizeof(int));
s.Ct_b=(float*)malloc(min*sizeof(float));
s.Ct_hb=(float*)malloc((((nombre_contraintes>nombre_var)?nombre_contraintes:nombre_var)-min)*sizeof(float));
s.vect_col_hb=(int*)malloc((((nombre_contraintes>nombre_var)?nombre_contraintes:nombre_var)-min)*sizeof(int));
Systeme_lineaire final;
Systeme_lineaire ** trace=(Systeme_lineaire**)malloc(sizeof(Systeme_lineaire*));
*trace=(Systeme_lineaire*)malloc(sizeof(Systeme_lineaire));

Simplexe(s,trace/*,&final*/);




}
