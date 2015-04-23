#!/usr/bin/python
# -*- coding: utf-8 -*-
import random

#Bu operasyon 1000 defa yapacağız için, 'for' statement ile onu yapıyoruz
for i in range(1,1001):
    
    #burda biz kaçıncı defa bu iş tekrarlanıyoruz, yazıyoruz
    print ("\n\n"+str(i)+". defa")
    
    #sans'a yeni random değer veriyoruz
    sans=random.randrange(1,10,1)
    
    #kullanının tercihi okuyoruz
    tercih=input("Tercihinizi yazin: ")
    
    #Tercih ve sans farklı olunca kadar, tercih'e yeni random değer veriyorz
    while(tercih==sans):
        tercih=random.randrange(1,10,1)
        
    #kullanıcı değiştirme istiyor mu ?
    x=input(str(tercih)+" mi "+str(sans)+" mi:")
    
    #Kontrol etmek
    if(x==sans):
        print("Kazandiniz")
    else:
        print("Yanlis Maalesef!")
