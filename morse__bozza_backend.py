import serial
import time

arduino = serial.Serial('COM4', 9600)
time.sleep(1)

#definisco le variabili e il dizionario 
chiave = {
    'a': '01',
    'A': '01',
    'b': '1000',
    'B': '1000',
    'c': '1010',
    'C': '1010',
    'd': '100',
    'D': '100',
    'e': '0',
    'E': '0',
    'f': '0010',
    'F': '0010',
    'g': '110',
    'G': '110',
    'h': '0000',
    'H': '0000',
    'i': '00',
    'I': '00',
    'j': '0111',
    'J': '0111',
    'k': '101',
    'K': '101',
    'l': '0100',
    'L': '0100',
    'm': '11',
    'M': '11',
    'n': '10',
    'N': '10',
    'o': '111',
    'O': '111',
    'p': '0110',
    'P': '0110',
    'q': '1101',
    'Q': '1101',
    'r': '010',
    'R': '010',
    's': '000',
    'S': '000',
    't': '1',
    'T': '1',
    'u': '001',
    'U': '001',
    'v': '0001',
    'V': '0001',
    'w': '011',
    'W': '011',    
    'x': '1001',
    'X': '1001',
    'y': '1011',
    'Y': '1011', 
    'z': '1100',
    'Z': '1100',
    '0': '11111',
    '1': '01111',
    '2': '00111',
    '3': '00011',
    '4': '00001',
    '5': '00000',
    '6': '10000',
    '7': '11000',
    '8': '11100',
    '9': '11110',
    '&': '01000',
    '"': '010010',
    "'": '011110',
    '@': '011010',
    ')': '101101',
    '(': '10110',
    ':': '111000',
    ',': '110011',
    '=': '10001',
    '!': '101011',
    '.': '010101',
    '-': '100001',
    '*': '1001',
    '%': '111111001011111',
    '+': '01010',
    '?': '001100',
    '/': '10010',
    'À': '01101',
    'à': '01101',
    }

chiave_inversa = {valore: carattere for carattere, valore in chiave.items()}

#definisco le funzioni criptaggio e di decriptaggio

# Fx CRIPTA
def cripta(testo):
    testo_criptato = ''
    sequenza_criptata = ''
    
    for carattere in testo:
        if carattere == ' ':
            if sequenza_criptata:
                testo_criptato += sequenza_criptata + '/'
                sequenza_criptata = ''
        else:
            sequenza_criptata += chiave.get(carattere, carattere) + ' '

    if sequenza_criptata:
        testo_criptato += sequenza_criptata
    
    return testo_criptato.rstrip('/')

#Fx DECRIPTA
def decripta(testo_criptato):
    testo_decriptato = ''
    sequenze = testo_criptato.split('/')
    
    for sequenza in sequenze:
        sequenza_caratteri = sequenza.strip().split()
        for sequenza_carattere in sequenza_caratteri:
            if sequenza_carattere in chiave_inversa:
                testo_decriptato += chiave_inversa[sequenza_carattere]
            else:
               
                return ''
        testo_decriptato += ' '  
    
    return testo_decriptato

#Fx interazione con Arduino
def serialMorse(testo_dainviare):
    arduino.write(testo_dainviare.encode())
#codice
while True:
    val = input("Inserisci il testo da criptare: ")
    criptato = cripta(val)
    invio = criptato+val+"\n"
    arduino.write(invio.encode())
    #testo = input()
    #testo_criptato = cripta(testo)
    #serialMorse(testo_criptato)
    #print("Testo criptato:", testo_criptato)
