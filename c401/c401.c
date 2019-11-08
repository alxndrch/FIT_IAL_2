/* c401.c: **********************************************************}
{* Téma: Rekurzivní implementace operací nad BVS
**                                         Vytvořil: Petr Přikryl, listopad 1994
**                                         Úpravy: Andrea Němcová, prosinec 1995
**                                                      Petr Přikryl, duben 1996
**                                                   Petr Přikryl, listopad 1997
**                                  Převod do jazyka C: Martin Tuček, říjen 2005
**                                         Úpravy: Bohuslav Křena, listopad 2009
**                                                 Karel Masařík, říjen 2013
**                                                 Radek Hranický 2014-2018
**
** Implementujte rekurzivním způsobem operace nad binárním vyhledávacím
** stromem (BVS; v angličtině BST - Binary Search Tree).
**
** Klíčem uzlu stromu je jeden znak (obecně jím může být cokoliv, podle
** čeho se vyhledává). Užitečným (vyhledávaným) obsahem je zde integer.
** Uzly s menším klíčem leží vlevo, uzly s větším klíčem leží ve stromu
** vpravo. Využijte dynamického přidělování paměti.
** Rekurzivním způsobem implementujte následující funkce:
**
**   BSTInit ...... inicializace vyhledávacího stromu
**   BSTSearch .... vyhledávání hodnoty uzlu zadaného klíčem
**   BSTInsert .... vkládání nové hodnoty
**   BSTDelete .... zrušení uzlu se zadaným klíčem
**   BSTDispose ... zrušení celého stromu
**
** ADT BVS je reprezentován kořenovým ukazatelem stromu (typ tBSTNodePtr).
** Uzel stromu (struktura typu tBSTNode) obsahuje klíč (typu char), podle
** kterého se ve stromu vyhledává, vlastní obsah uzlu (pro jednoduchost
** typu int) a ukazatel na levý a pravý podstrom (LPtr a RPtr). Přesnou definici typů
** naleznete v souboru c401.h.
**
** Pozor! Je třeba správně rozlišovat, kdy použít dereferenční operátor *
** (typicky při modifikaci) a kdy budeme pracovat pouze se samotným ukazatelem
** (např. při vyhledávání). V tomto příkladu vám napoví prototypy funkcí.
** Pokud pracujeme s ukazatelem na ukazatel, použijeme dereferenci.
**/

#include "c401.h"
int solved;

void BSTInit (tBSTNodePtr *RootPtr) { // ukazatel na ukazatel
/*   -------
** Funkce provede počáteční inicializaci stromu před jeho prvním použitím.
**
** Ověřit, zda byl již strom předaný přes RootPtr inicializován, nelze,
** protože před první inicializací má ukazatel nedefinovanou (tedy libovolnou)
** hodnotu. Programátor využívající ADT BVS tedy musí zajistit, aby inicializace
** byla volána pouze jednou, a to před vlastní prací s BVS. Provedení
** inicializace nad neprázdným stromem by totiž mohlo vést ke ztrátě přístupu
** k dynamicky alokované paměti (tzv. "memory leak").
**
** Všimněte si, že se v hlavičce objevuje typ ukazatel na ukazatel.
** Proto je třeba při přiřazení přes RootPtr použít dereferenční operátor *.
** Ten bude použit i ve funkcích BSTDelete, BSTInsert a BSTDispose.
**/	
    // koren stromu je null
    // PP mu bude pridelen az ve funkci insert
    *RootPtr = NULL;

}

int BSTSearch (tBSTNodePtr RootPtr, char K, int *Content){ //ukazatel na ukazatel
/*  ---------
** Funkce vyhledá uzel v BVS s klíčem K.
**
** Pokud je takový nalezen, vrací funkce hodnotu TRUE a v proměnné Content se
** vrací obsah příslušného uzlu.´Pokud příslušný uzel není nalezen, vrací funkce
** hodnotu FALSE a obsah proměnné Content není definován (nic do ní proto
** nepřiřazujte).
**
** Při vyhledávání v binárním stromu bychom typicky použili cyklus ukončený
** testem dosažení listu nebo nalezení uzlu s klíčem K. V tomto případě ale
** problém řešte rekurzivním volání této funkce, přičemž nedeklarujte žádnou
** pomocnou funkci.
**/
    if(RootPtr == NULL){ // neexistuje koren
        return FALSE;
    }else{
        if(K == RootPtr->Key){ // klic byl nalezen
            *Content = RootPtr->BSTNodeCont;
            return TRUE;
        }else{
            if(K > RootPtr->Key){ // hledany klic je vetsi
                return  BSTSearch(RootPtr->RPtr, K, Content); // prochazime pravou vetev    
            }else{ // hledany klic je mensi
                return BSTSearch(RootPtr->LPtr, K, Content); // prochazime levou vetev
            }
        }
    }
}


void BSTInsert (tBSTNodePtr* RootPtr, char K, int Content) { //ukazatel na ukazatel
/*   ---------
** Vloží do stromu RootPtr hodnotu Content s klíčem K.
**
** Pokud již uzel se zadaným klíčem ve stromu existuje, bude obsah uzlu
** s klíčem K nahrazen novou hodnotou. Pokud bude do stromu vložen nový
** uzel, bude vložen vždy jako list stromu.
**
** Funkci implementujte rekurzivně. Nedeklarujte žádnou pomocnou funkci.
**
** Rekurzivní implementace je méně efektivní, protože se při každém
** rekurzivním zanoření ukládá na zásobník obsah uzlu (zde integer).
** Nerekurzivní varianta by v tomto případě byla efektivnější jak z hlediska
** rychlosti, tak z hlediska paměťových nároků. Zde jde ale o školní
** příklad, na kterém si chceme ukázat eleganci rekurzivního zápisu.
**/

    if(*RootPtr == NULL){ // neexistuje uzel s hledanym klicem 
        *RootPtr = (struct tBSTNode*) malloc(sizeof(struct tBSTNode)); // vytvorime novy uzel
        
        if(*RootPtr != NULL){ // inicializace noveho uzlu
            (*RootPtr)->Key = K;
            (*RootPtr)->BSTNodeCont = Content;
	    (*RootPtr)->LPtr = NULL;
	    (*RootPtr)->RPtr = NULL;
        }
    }else{
        if (K > (*RootPtr)->Key){ // hledany klic je vetsi
	    BSTInsert(&((*RootPtr)->RPtr), K, Content); // prochazime pravou vetev
        }else if(K < (*RootPtr)->Key){ // hledany klic je mensi
	    BSTInsert(&((*RootPtr)->LPtr), K, Content); // prochazime levou vetev
        }else{
	    (*RootPtr)->BSTNodeCont = Content; // byl nalezen klic, aktualizujeme data
	}
    }

}

void ReplaceByRightmost (tBSTNodePtr PtrReplaced, tBSTNodePtr *RootPtr) { //žere ukazatel , a ukazatel na ukazatel
/*   ------------------
** Pomocná funkce pro vyhledání, přesun a uvolnění nejpravějšího uzlu.
**
** Ukazatel PtrReplaced ukazuje na uzel, do kterého bude přesunuta hodnota
** nejpravějšího uzlu v podstromu, který je určen ukazatelem RootPtr.
** Předpokládá se, že hodnota ukazatele RootPtr nebude NULL (zajistěte to
** testováním před volání této funkce). Tuto funkci implementujte rekurzivně.
**
** Tato pomocná funkce bude použita dále. Než ji začnete implementovat,
** přečtěte si komentář k funkci BSTDelete().
**/

	// hledame maximum leveho podstromu
    if(PtrReplaced != NULL){
        if(*RootPtr == NULL){ // vstoupime do leveho podstromu pokud tam nejsme 
            ReplaceByRightmost(PtrReplaced, &(PtrReplaced->LPtr));
        }else if(*RootPtr != NULL){
                
            if((*RootPtr)->RPtr == NULL){ // pokud jsme v maximu levehe podstromu
		// provedeme vymenu
                PtrReplaced->Key = (*RootPtr)->Key;
		PtrReplaced->BSTNodeCont = (*RootPtr)->BSTNodeCont;
			
		PtrReplaced->LPtr = (*RootPtr)->LPtr;
			
            }else{ // pokud nejsme v maximu hledame dal
                if((*RootPtr)->RPtr->RPtr == NULL){ 
                    tBSTNodePtr temp = (*RootPtr)->RPtr;

                    PtrReplaced->Key = temp->Key;
                    PtrReplaced->BSTNodeCont = temp->BSTNodeCont;

                    (*RootPtr)->RPtr = temp->LPtr;
                        
                    free(temp);
                    temp = NULL;
	
		}else{
		    ReplaceByRightmost(PtrReplaced, &((*RootPtr)->RPtr));	
		}
	    }
	}
    }
}

void BSTDelete (tBSTNodePtr *RootPtr, char K) { // ukazatel na ukazatel
/*   ---------
** Zruší uzel stromu, který obsahuje klíč K.
**
** Pokud uzel se zadaným klíčem neexistuje, nedělá funkce nic.
** Pokud má rušený uzel jen jeden podstrom, pak jej zdědí otec rušeného uzlu.
** Pokud má rušený uzel oba podstromy, pak je rušený uzel nahrazen nejpravějším
** uzlem levého podstromu. Pozor! Nejpravější uzel nemusí být listem.
**
** Tuto funkci implementujte rekurzivně s využitím dříve deklarované
** pomocné funkce ReplaceByRightmost.
**/	

    if(*RootPtr != NULL){
        if(K > (*RootPtr)->Key){ // hledany klic je vetsi
            BSTDelete(&((*RootPtr)->RPtr),K); // jdeme pravou vetvi
        }else if(K < (*RootPtr)->Key){ // hledany klic je mensi 
            BSTDelete(&((*RootPtr)->LPtr),K); // jdeme levou vetvi
        }else{ // nasli jsme klic

            tBSTNodePtr temp = (*RootPtr);
            
            if((*RootPtr)->LPtr == NULL && (*RootPtr)->RPtr == NULL){ // koren nema potomky 
                free(*RootPtr); // zrusime koren
                *RootPtr = NULL; 
            }else if((*RootPtr)->LPtr == NULL){ // koren nema leveho potomka
                
                *RootPtr = temp->RPtr; // koren nahradime pravym potomkem
                temp->RPtr = NULL; // ukazatel na praveho potomka zrusime
                
                free(temp);
                temp = NULL;				
            
            }else if((*RootPtr)->RPtr == NULL){ // koren nema praveho potomka
                
                *RootPtr = temp->LPtr; // koren nahradime levym potomkem
                temp->LPtr = NULL; // ukazatel na leveho potomka zrusime
                
                free(temp);
                temp = NULL;
            
            }else{ // koren ma oba potomky 
                ReplaceByRightmost(*RootPtr,&((*RootPtr)->LPtr));
            }
        }	
    }
}

void BSTDispose (tBSTNodePtr *RootPtr) { //žere ukazatel na ukazatel
/*   ----------
** Zruší celý binární vyhledávací strom a korektně uvolní paměť.
**
** Po zrušení se bude BVS nacházet ve stejném stavu, jako se nacházel po
** inicializaci. Tuto funkci implementujte rekurzivně bez deklarování pomocné
** funkce.
**/
    if(*RootPtr != NULL){ //bude pokracovat dokud nenarazi na list
        BSTDispose(&((*RootPtr)->LPtr)); //smazeme levou vetev, argument - adresa ukazatele LPtr
        BSTDispose(&((*RootPtr)->RPtr)); //smazeme pravou vetev argument - adresa ukazatele RPtr

        free(*RootPtr); //smazeme list
	BSTInit(RootPtr); //uvedeme strom do puvodniho stavu

    }
}

/* konec c401.c */

