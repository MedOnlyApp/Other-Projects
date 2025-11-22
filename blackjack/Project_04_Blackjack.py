from termcolor import colored
import pyinputplus as py
import random
import time
import sys

HEARTS   = chr(9829) # Character 9829 is '♥'.
DIAMONDS = chr(9830) # Character 9830 is '♦'.
SPADES   = chr(9824) # Character 9824 is '♠'.
CLUBS    = chr(9827) # Character 9827 is '♣'.
SUITES = [HEARTS, DIAMONDS, SPADES, CLUBS]
RANKS = ['A', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'K', 'Q', 'J'] 


def print_colored_text (text, color):
    texte = colored(text, color)
    print(texte)

def add_card_values (thislist):     #### Fonction that  summes up the value of the cards
    total_list=[0,0]
    for x in thislist:
        if x[0] == 'K'  or x[0] == 'Q'  or x[0] == 'J':
            total_list[0] += 10
            total_list[1] += 10
        elif x[0] == 'A':
            total_list[0] += 1
            total_list[1] += 11
        else :
            total_list[0] += int(x[0])
            total_list[1] += int(x[0])
    return total_list
        
        

def choose_random_card (thislist):     ### Choose a random card
    rank = random.choice(RANKS)
    suit = random.choice(SUITES)
    thislist.append([rank,suit])
    #thisdict.update({suit : rank})
    return thislist


def print_cards (thislist):       ### Fonction that prints the cards
    card = ['' ,'' ,'' ,'']
    for x in thislist:
        card[0] += ' ___   '
        card[2] += f'| {x[1]} |  '
        if x[0] != '10':
            card[1] += f'|{x[0]}  |  '
            card[3] += f'|__{x[0]}|  '
        else :
            card[1] += f'|{x[0]} |  '
            card[3] += f'|_{x[0]}|  '

    for y in card:
        print(y)

def compare_points (player_list ,dealer_list ,bet ,money):    ### Fonction that compares the player's point with the dealer's
    player_list.sort() ,dealer_list.sort()
    
    while player_list[-1] > 21 or dealer_list[-1] > 21: 
        if player_list[-1] > 21 : player_list.pop(-1)
        if dealer_list[-1] > 21 : dealer_list.pop(-1)

    if player_list[-1] == 21:
        print('You have got Blackjack!')
        money += bet * 1.5
        print('Your wallet : $',money)
        return money
    if player_list[-1] > dealer_list[-1]: 
        print(f'you win {bet*2}')
        money += bet * 2
        print('Your wallet : $',money)
        return money
    elif  player_list[-1] < dealer_list[-1]: 
        print(f'you lose !')
        print('Your wallet : $',money)
        return  money
    else :
        print(f"It's a Draw")
        money += bet
        print('Your wallet : $',money)
        return money


def play_again (Wallet):
    repeat = py.inputYesNo('\n\nWould you like to play another game : ').lower()
    if repeat[0] == 'y': main(Wallet)
    else : sys.exit()


def main(Wallet):
    dealer_cards = []
    player_cards = []

    Bet = py.inputNum(f'how much would you like to bet ? (1-{Wallet}) : ', min=1, max=5000)
    print(f'Bet : {Bet}')
    Wallet-= Bet

    for a in range(2):
        player_cards = choose_random_card(player_cards)
        if a == 0:
            dealer_cards = choose_random_card(dealer_cards)
        else : 
            dealer_cards.append(['#' ,'#'])

    print_colored_text('\nDealer : ???\n' ,'yellow')
    print_cards(dealer_cards)
    print_colored_text(f'\nPlayer : {add_card_values(player_cards) if add_card_values(player_cards)[1]!=add_card_values(player_cards)[0] else add_card_values(player_cards)[0]}' ,'yellow')
    print_cards(player_cards)

    #Wallet = compare_points(add_card_values(player_cards) ,add_card_values(dealer_cards) ,Bet ,Wallet)
    


    choice = py.inputStr('\n\n(H)it, (S)tand, (D)ouble down : ').lower()

    if choice == 'd' :
        Wallet -= Bet
        Bet *= 2
        player_cards = choose_random_card(player_cards)
        print_colored_text(f'\nPlayer : {add_card_values(player_cards) if add_card_values(player_cards)[1]!=add_card_values(player_cards)[0] else add_card_values(player_cards)[0]}' ,'yellow')
        print_cards(player_cards)
        choice = 's'



    while choice =='h' and (add_card_values(player_cards)[0] < 21 or add_card_values(player_cards)[1] < 21):
        player_cards = choose_random_card(player_cards)
        print_colored_text(f'\nPlayer : {add_card_values(player_cards) if add_card_values(player_cards)[1]!=add_card_values(player_cards)[0] else add_card_values(player_cards)[0]}' ,'yellow')
        print_cards(player_cards)
        if (add_card_values(player_cards)[0] < 21 or add_card_values(player_cards)[1] < 21):
            choice = py.inputStr('\n\n(H)it, (S)tand : ').lower()
        else : choice = 's'

    if choice == 'h':
        print("You can't hit anymore")
        choice = 's'


    if choice == 's' :

        dealer_cards.remove(['#' ,'#'])
        dealer_cards = choose_random_card(dealer_cards)
        print_colored_text(f'\nDealer : {add_card_values(dealer_cards) if add_card_values(dealer_cards)[1]!=add_card_values(dealer_cards)[0] else add_card_values(dealer_cards)[0]}' ,'yellow')
        print_cards(dealer_cards)

        print_colored_text(f'\nPlayer : {add_card_values(player_cards) if add_card_values(player_cards)[1]!=add_card_values(player_cards)[0] else add_card_values(player_cards)[0]}' ,'yellow')
        print_cards(player_cards)

    while add_card_values(dealer_cards)[0] <= 16 and add_card_values(dealer_cards)[1] <= 16:
        time.sleep(2)
        dealer_cards = choose_random_card(dealer_cards)
        print_colored_text(f'\nDealer : {add_card_values(dealer_cards) if add_card_values(dealer_cards)[1]!=add_card_values(dealer_cards)[0] else add_card_values(dealer_cards)[0]}' ,'yellow')
        print_cards(dealer_cards)

        print_colored_text(f'\nPlayer : {add_card_values(player_cards) if add_card_values(player_cards)[1]!=add_card_values(player_cards)[0] else add_card_values(player_cards)[0]}' ,'yellow')
        print_cards(player_cards)
        
    if  add_card_values(player_cards)[0] > 21 and add_card_values(player_cards)[1] > 21:
        print('\nYou lose !')
        print('Your wallet : $',Wallet)
        play_again(Wallet)

    if  add_card_values(dealer_cards)[0] > 21 and add_card_values(dealer_cards)[1] > 21:
        print(f'\nDealer bust ! You win {Bet * 2}')
        Wallet  += Bet * 2
        print('Your wallet : $',Wallet)
        play_again(Wallet)

    if  add_card_values(dealer_cards)[0] <= 21 or add_card_values(dealer_cards)[1] <= 21:
        Wallet = compare_points(add_card_values(player_cards) ,add_card_values(dealer_cards) ,Bet ,Wallet)
    
    play_again(Wallet)

 
 

print('''Rules:
      Try to get as close to 21 without going over.
      Kings, Queens, and Jacks are worth 10 points.
      Aces are worth 1 or 11 points.
      Cards 2 through 10 are worth their face value.
      (H)it to take another card.
      (S)tand to stop taking cards.
      On your first play, you can (D)ouble down to increase your bet
      but must hit exactly one more time before standing.
      In case of a tie, the bet is returned to the player.
      The dealer stops hitting at 17.''')

Wallet = 5000.0
main(Wallet)




