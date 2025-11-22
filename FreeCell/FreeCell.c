#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



typedef struct {
    char *number;
    char *color;
    // char *suit;
    int suit;
} Card;


typedef struct FreeCell
{
    Card *card;
    struct FreeCell *next;
}Deck;

// ! fonctions pour changer les couleur d'écriture et de background
void Red()
{
    printf("\033[%dm", 30 + 1);
    printf("\033[%dm", 40 + 7);
}
void Black()
{
    printf("\033[%dm", 30 + 0);
    printf("\033[%dm", 40 + 7);
}
void ResetColor()
{
    printf("\033[%dm", 30 + 7);
    printf("\033[%dm", 40 + 0);
}
void changeColor(Card *card){
    if(strcmp(card->color, "red") == 0)
        Red();
    else
        Black();
}
// ! //////////////////////////////////////////////////////////////

// ! les fonctions principales des piles (isEmpty, push, peek, pop)
Deck* CreateElement(Card *card){
    Deck* newElement = (Deck*)malloc(sizeof(Deck));
    newElement->card = card;
    newElement->next = NULL;

    return newElement;
}

int isEmpty(Deck *head){
    if ( head == NULL )
        return 1;
    else
        return 0;
}

void push(Card *card, Deck **head){
    Deck* newElement;
    newElement = CreateElement(card);
    newElement->next = *head;
    *head = newElement;
}

Card* peek(Deck *head){
    if (head == NULL)
        return NULL;
    else
        return head->card;
}

void pop(Deck **head){
    if (head == NULL)
        return;
    else{
        Deck* tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}
// ! //////////////////////////////////////////////////////////////

int help_shuffle() {
    // if ( number < 0 ) number *= -1;

    long number = time(NULL);

    int wahadat = 0;
    int acharat = 0;

    while ( number % 10 != 0 )
    {
        number--;
        wahadat++;
    }
    
    while ( number % 100 != 0 )
    {
        number -= 10;
        acharat += 10;
    }

    return wahadat+acharat;
    


}

// ! Mixer les cartes d'order quelconque 
void shuffle(Card *Tab, int n)
{
    if (n > 1) 
    {
        Card tmp;
        int i;
        int aide = help_shuffle();
        printf("\naide = %d\n", aide);
        for (i = 0; i < n - 1; i++) 
        {
            int j = (rand() + aide) % (52);
            tmp = Tab[j];
            Tab[j] = Tab[i];
            Tab[i] = tmp;
        }
    }
}

// ! Retourner le nombre de carte en type int (1-13) 
int Cards_Number(char *card){
    
    // * Get card 2 number
    int card_number;
    if ( card[1] == ' ' )
    {
        if ( card[0] == 'A' )
            card_number = 1;
        else if ( card[0] == 'J' )
            card_number = 11;
        else if ( card[0] == 'Q' )
            card_number = 12;
        else if ( card[0] == 'K' )
            card_number = 13;
        else                            // * if ( (int)(card1[1]) >= 50 && (int)(card1[1]) <= 57 )
            card_number = card[0] - 48;
    }else {
        card_number = 10;
    }


    return card_number;

}

// ! Retourner 1 si deux cartes sont ordonnée
int Cards_Order(char *card1, char *card2){
    
    // * Get card 2 number
    int card1_number;
    if ( card1[1] == ' ' )
    {
        if ( card1[0] == 'A' )
            card1_number = 1;
        else if ( card1[0] == 'J' )
            card1_number = 11;
        else if ( card1[0] == 'Q' )
            card1_number = 12;
        else if ( card1[0] == 'K' )
            card1_number = 13;
        else                            // * if ( (int)(card1[1]) >= 50 && (int)(card1[1]) <= 57 )
            card1_number = card1[0] - 48;
    }else {
        card1_number = 10;
    }

    // * Get card 2 number
    int card2_number;
    if ( card2[1] == ' ' )
    {
        if ( card2[0] == 'A' )
            card2_number = 1;
        else if ( card2[0] == 'J' )
            card2_number = 11;
        else if ( card2[0] == 'Q' )
            card2_number = 12;
        else if ( card2[0] == 'K' )
            card2_number = 13;
        else                            // ! if ( (int)(card1[1]) >= 50 && (int)(card1[1]) <= 57 )
            card2_number = card2[0] - 48;
    }else {
        card2_number = 10;
    }
    
    printf("\n%d:%d",card1_number, card2_number);
    if ( card1_number+1 == card2_number )
        return 1;
    else
        return 0;

}

// ! renverser un nombre de carte dans un stack, utilisée dans le deplacement des cartes dand la zone 3
void Reverse_cards_in_stack(Deck *stacks_Tab[], Deck *element, int index) {
    if ( stacks_Tab[index] == NULL || stacks_Tab[index]->next == NULL || element == NULL )
        return ;

    if ( stacks_Tab[index]->next == element ) 
    {
        stacks_Tab[index]->next = element->next;
        element->next = stacks_Tab[index];
        stacks_Tab[index] = element;
    }else {
        Deck *i, *last, *tmp;
        last = stacks_Tab[index];
        i = stacks_Tab[index]->next;

        last->next = element->next;

        while ( last != element ) {
            tmp = i->next;
            i->next = last;
            last = i;
            i = tmp;
        }
        stacks_Tab[index] = element;
    }
}

// ! fonctions pour afficher les cartes
int PrintCard(Deck *stack, int number){

    Deck *i=NULL;
    int n = 0;

    i = stack;
    while ( i != NULL )
    {
        n++;
        i = i->next;
    }
    number = n - number;
    n = 0;

    i = stack;
    while ( i != NULL )
    {
        if ( number == n ) {
            changeColor(i->card);
            printf("%s%c\t", i->card->number, i->card->suit);
            ResetColor();
            return 1;
        }
        n++;
        i = i->next;
    }
    printf("    \t");
    
    return 0;
    
}

void Print_stacks(Deck *stacks_Tab[], Deck *full_Tab[], Deck *Ones_Tab[]){

    int ligne = 0;

    int full = 0;

    printf("\n\n===========Zone01===========  ");
    printf("  ===========Zone02===========\n\n");
    for ( int i = 0 ; i < 4 ; i++ )
    {
        if ( isEmpty(full_Tab[i]) == 0 ) // * if the stack is not empty
        {
            changeColor(full_Tab[i]->card);
            printf("%s%c\t", full_Tab[i]->card->number, full_Tab[i]->card->suit);
            ResetColor();
            full += Cards_Number(full_Tab[i]->card->number);
        }
        else
            printf("[  ]\t");
    }

    Deck *j=NULL;
    int ones = 0;
    for ( int i = 0 ; i < 4 ; i++ )
    {
        if ( isEmpty(Ones_Tab[i]) == 0 ) // * if the stack is not empty
        {
            changeColor(Ones_Tab[i]->card);
            printf("%s%c\t", Ones_Tab[i]->card->number, Ones_Tab[i]->card->suit);
            ResetColor();
                
            ones++;
        }
        else
            printf("[  ]\t");
    }

    printf("\n\n===========================Zone03===========================\n");

    for (int i = 0, j = 0; j < 52-ones-full; i++)
    {
        if ( i % 8 == 0 ){
            ligne++;
            printf("\n");
        }

        if ( PrintCard(stacks_Tab[i%8], ligne) == 1 )//{}
            j++;
        
    }
    printf("\n\n============================================================\n");
    
}

void Print_one_stack(Deck *stack){
    Deck *i;

    i = stack;
    while ( i != NULL )
    {
        changeColor(i->card);
        printf("%s%c\t", i->card->number, i->card->suit);
        ResetColor();
        i = i->next;
    }

    printf("\n\n<<==============Fin Stack=============>> \n\n");
    
}
// ! //////////////////////////////////

// ! Fonction pour remplir les stacks de la zone 3
void init_stacks(Deck *stacks_Tab[], Card *Card_Tab){

    shuffle(Card_Tab, 52);

    for ( int i = 0 ; i < 52 ; i++ )
    {
        push(Card_Tab+i, stacks_Tab + i%8);
    }

}

// ! fonctions pour deplacer les cartes d'une zone vers l'autre, et d'un stack vers l'autre
void Zone2_to_Zone1(Deck *Ones_Tab[], Deck *full_Tab[], int from_index, int to_index){
    if ( isEmpty(Ones_Tab[from_index-1]) == 1 )
    {
        printf("\nStack %d in Zone 2 is empty", from_index);
    }
    else if ( isEmpty(full_Tab[to_index-1]) == 1 )
    {
        if ( strcmp(Ones_Tab[from_index-1]->card->number, "A  ") == 0 ){
            // * Move from Zone 2 to Zone 1
            push(Ones_Tab[from_index-1]->card, full_Tab+to_index-1);
            pop(Ones_Tab+from_index-1);
        }
        else {
            printf("\nInvalide move");
        }

    }else if ( Cards_Order(full_Tab[to_index-1]->card->number, Ones_Tab[from_index-1]->card->number) == 1 ){
            push(Ones_Tab[from_index-1]->card, full_Tab+to_index-1);
            pop(Ones_Tab+from_index-1);
    }else
        printf("\nInvalide move");

}

void Zone2_to_Zone3(Deck *Ones_Tab[], Deck *stacks_Tab[], int from_index, int to_index){

    if ( isEmpty(Ones_Tab[from_index-1]) == 1 )
    {
        printf("\nStack %d in Zone 2 is empty", from_index);
    }else if ( isEmpty(stacks_Tab[to_index-1]) == 1 )
    {
        // * Move from Zone 2 to Zone 3
        push(Ones_Tab[from_index-1]->card, stacks_Tab+to_index-1);
        pop(Ones_Tab+from_index-1);
    }
    else if ( strcmp(Ones_Tab[from_index-1]->card->color, stacks_Tab[to_index-1]->card->color) == 0 || Cards_Order(Ones_Tab[from_index-1]->card->number, stacks_Tab[to_index-1]->card->number) != 1 ){
        printf("\nInvalide move");
    }else if ( strcmp(Ones_Tab[from_index-1]->card->color, stacks_Tab[to_index-1]->card->color) != 0 && Cards_Order(Ones_Tab[from_index-1]->card->number, stacks_Tab[to_index-1]->card->number) == 1 ) {
        // * Move from Zone 2 to Zone 3
        push(Ones_Tab[from_index-1]->card, stacks_Tab+to_index-1);
        pop(Ones_Tab+from_index-1);
    }

}

void Zone3_to_Zone1(Deck *stacks_Tab[], Deck *full_Tab[], int from_index, int to_index){
    printf("\nmoh1");
    if ( isEmpty(stacks_Tab[from_index-1]) == 1 )
    {
        printf("\nStack %d in Zone 3 is empty", from_index);
    }
    else if ( isEmpty(full_Tab[to_index-1]) == 1 )
    {
    printf("\nmoh2");
        if ( strcmp(stacks_Tab[from_index-1]->card->number, "A  ") == 0 ){
    printf("\nmoh3");
            push(stacks_Tab[from_index-1]->card, full_Tab+to_index-1);
            pop(stacks_Tab+from_index-1);
        }else{
            printf("\nInvalide move1");
        }
        
    }else if ( strcmp(stacks_Tab[from_index-1]->card->color, full_Tab[to_index-1]->card->color) != 0 )
    {
        printf("\nInvalide move2");
    }else if ( Cards_Order(full_Tab[to_index-1]->card->number, stacks_Tab[from_index-1]->card->number) == 1 )
    {
    printf("\nmoh4");
        push(stacks_Tab[from_index-1]->card, full_Tab+to_index-1);
        pop(stacks_Tab+from_index-1);            
    }else{
        printf("\nInvalide move3");
    }
}

void Zone3_to_Zone2(Deck *stacks_Tab[], Deck *Ones_Tab[], int from_index, int to_index){

    if ( isEmpty(stacks_Tab[from_index-1]) == 1 )
    {
        printf("\nStack %d in Zone 3 is empty", from_index);
    }
    else if ( isEmpty(Ones_Tab[to_index-1]) == 1 )
    {
        push(stacks_Tab[from_index-1]->card, Ones_Tab+to_index-1);
        pop(stacks_Tab+from_index-1);
        
    }else{
        printf("\nInvalide move");
    }
}

void Zone3_to_Zone3(Deck *stacks_Tab[], int from_index, int to_index, int cards_nbr){
    printf("\nmoh1");
    if ( isEmpty(stacks_Tab[from_index-1]) == 1 )
    {
        printf("\nStack %d in Zone 3 is empty", from_index);
    }else {
    printf("\nmoh2");
        if ( cards_nbr == 1 ) {
    printf("\nmoh3");
            if ( isEmpty(stacks_Tab[to_index-1]) == 1 || ( Cards_Order(stacks_Tab[from_index-1]->card->number, stacks_Tab[to_index-1]->card->number) == 1 && strcmp(stacks_Tab[from_index-1]->card->color, stacks_Tab[to_index-1]->card->color) != 0 ) ) {
                push(stacks_Tab[from_index-1]->card, stacks_Tab+to_index-1);
                pop(stacks_Tab+from_index-1);
            }else {
                printf("\nInvalide move1");
            }
        }else if ( cards_nbr <= 1 || stacks_Tab[from_index-1]->next == NULL )
        {
            printf("\nInvalide move2");
        }else {
            int c = 1;
            Deck *i = NULL, *last;
            i = stacks_Tab[from_index-1];
            while ( i != NULL ) {
                i = i->next;
                c++;
            }
            if ( c < cards_nbr ) 
                printf("\nInvalide move3");
            else {
                last = stacks_Tab[from_index-1];
                i = stacks_Tab[from_index-1]->next;
                c = 2;
                while ( c <= cards_nbr ) {
                    if ( Cards_Order(last->card->number, i->card->number) == 1 && strcmp(last->card->color, i->card->color) != 0 )
                    {
                        c++;
                        last = i;
                        i = i->next;
                    }else{
                        printf("\nInvalide move4");
                        break;
                    }
                } 
                if ( c-1 == cards_nbr )
                {
                    if ( isEmpty(stacks_Tab[to_index-1]) == 1 || ( Cards_Order(last->card->number, stacks_Tab[to_index-1]->card->number) == 1 && strcmp(last->card->color, stacks_Tab[to_index-1]->card->color) != 0 ) )
                    {
                        Reverse_cards_in_stack(stacks_Tab, last, from_index-1);
                        c = 1;
                        i = stacks_Tab[from_index-1];
                        while ( c <= cards_nbr ) {
                            push(i->card, stacks_Tab+to_index-1);
                            pop(stacks_Tab+from_index-1);
                            c++;
                            i = i->next;
                        }

                    }else {
                        printf("\nInvalide move5");
                    }

                }
            }
        }
    }
}
// ! ///////////////////////////////////////////////////////////////////////////////////////








int main(){

    Card cards[52] = {{"A  ", "red", 0x3}, {"2  ", "red", 0x3}, {"3  ", "red", 0x3}, {"4  ", "red", 0x3}, {"5  ", "red", 0x3}, {"6  ", "red", 0x3}, {"7  ", "red", 0x3}, {"8  ", "red", 0x3}, {"9  ", "red", 0x3}, {"10 ", "red", 0x3}, {"J  ", "red", 0x3}, {"Q  ", "red", 0x3}, {"K  ", "red", 0x3},
                    {"A  ", "red", 0x4}, {"2  ", "red", 0x4}, {"3  ", "red", 0x4}, {"4  ", "red", 0x4}, {"5  ", "red", 0x4}, {"6  ", "red", 0x4}, {"7  ", "red", 0x4}, {"8  ", "red", 0x4}, {"9  ", "red", 0x4}, {"10 ", "red", 0x4}, {"J  ", "red", 0x4}, {"Q  ", "red", 0x4}, {"K  ", "red", 0x4}, 
                    {"A  ", "black", 0x5}, {"2  ", "black", 0x5}, {"3  ", "black", 0x5}, {"4  ", "black", 0x5}, {"5  ", "black", 0x5}, {"6  ", "black", 0x5}, {"7  ", "black", 0x5}, {"8  ", "black", 0x5}, {"9  ", "black", 0x5}, {"10 ", "black", 0x5}, {"J  ", "black", 0x5}, {"Q  ", "black", 0x5}, {"K  ", "black", 0x5}, 
                    {"A  ", "black", 0x6}, {"2  ", "black", 0x6}, {"3  ", "black", 0x6}, {"4  ", "black", 0x6}, {"5  ", "black", 0x6}, {"6  ", "black", 0x6}, {"7  ", "black", 0x6}, {"8  ", "black", 0x6}, {"9  ", "black", 0x6}, {"10 ", "black", 0x6}, {"J  ", "black", 0x6}, {"Q  ", "black", 0x6}, {"K  ", "black", 0x6}, };

    Deck *Ones_Tab[4] = {NULL, NULL, NULL, NULL};
    Deck *full_Tab[4] = {NULL, NULL, NULL, NULL};
    Deck *stacks_Tab[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    init_stacks(stacks_Tab, cards);

    Print_stacks(stacks_Tab, full_Tab, Ones_Tab);

    
    int zone1, zone2;
    int stack1, stack2;

    while ( (full_Tab[0] == NULL || full_Tab[1] == NULL || full_Tab[2] == NULL || full_Tab[3] == NULL) || (full_Tab[0]->card->number != "K  " || full_Tab[1]->card->number != "K  " || full_Tab[2]->card->number != "K  " || full_Tab[3]->card->number != "K  ") ) {
        do {
            printf("\nfrom Zone : ");
            scanf("%d", &zone1);
        }while(zone1 <= 1 || zone1 > 3);
        
        do {
            printf("\nTo Zone : ");
            scanf("%d", &zone2);
        }while(zone2 < 1 || zone2 > 3);

        // ! from Zone 2 to Zone 1
        if ( zone1 == 2 && zone2 == 1 ) {
            do {
                printf("\nFrom Stack : ");
                scanf("%d", &stack1);
            }while(stack1 < 1 || stack1 > 4);
            do {
                printf("\nTo Stack : ");
                scanf("%d", &stack2);
            }while(stack2 < 1 || stack2 > 4);

            Zone2_to_Zone1(Ones_Tab, full_Tab, stack1, stack2);
        }
        // ! from Zone 2 to Zone 3
        else if ( zone1 == 2 && zone2 == 3 ) {
            do {
                printf("\nFrom Stack : ");
                scanf("%d", &stack1);
            }while(stack1 < 1 || stack1 > 4);
            do {
                printf("\nTo Stack : ");
                scanf("%d", &stack2);
            }while(stack2 < 1 || stack2 > 8);

            Zone2_to_Zone3(Ones_Tab, stacks_Tab, stack1, stack2);


        }
        // ! from Zone 3 to Zone 1
        else if ( zone1 == 3 && zone2 == 1 ) {
            do {
                printf("\nFrom Stack : ");
                scanf("%d", &stack1);
            }while(stack1 < 1 || stack1 > 8);
            do {
                printf("\nTo Stack : ");
                scanf("%d", &stack2);
            }while(stack2 < 1 || stack2 > 4);

            Zone3_to_Zone1(stacks_Tab, full_Tab, stack1, stack2);
        }
        // ! from Zone 3 to Zone 2
        else if ( zone1 == 3 && zone2 == 2 ) {
            do {
                printf("\nFrom Stack : ");
                scanf("%d", &stack1);
            }while(stack1 < 1 || stack1 > 8);
            do {
                printf("\nTo Stack : ");
                scanf("%d", &stack2);
            }while(stack2 < 1 || stack2 > 4);

            Zone3_to_Zone2(stacks_Tab, Ones_Tab, stack1, stack2);

        }
        // ! from Zone 3 to Zone 3
        else if ( zone1 == 3 && zone2 == 3 ) {
            int number_of_cards;
            do {
                printf("\nFrom Stack : ");
                scanf("%d", &stack1);
            }while(stack1 < 1 || stack1 > 8);
            do {
                printf("\nNumber of Cards : ");
                scanf("%d", &number_of_cards);
            }while(number_of_cards < 1 || number_of_cards > 52);
            do {
                printf("\nTo Stack : ");
                scanf("%d", &stack2);
            }while(stack2 < 1 || stack2 > 8);

            Zone3_to_Zone3(stacks_Tab, stack1, stack2, number_of_cards);
        }
        
        // Print_one_stack(stacks_Tab[0]);
        // Print_one_stack(stacks_Tab[1]);
        // Print_one_stack(stacks_Tab[2]);
        // Print_one_stack(stacks_Tab[3]);
        // Print_one_stack(stacks_Tab[4]);
        // Print_one_stack(stacks_Tab[5]);
        // Print_one_stack(stacks_Tab[6]);
        // Print_one_stack(stacks_Tab[7]);


        Print_stacks(stacks_Tab, full_Tab, Ones_Tab);

    }

    return 0;
}
