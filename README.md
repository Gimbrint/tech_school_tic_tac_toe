# Krustiņi un nullītes

Šī ir repo mūsu krustiņu un nullīšu spēlei.

## Kā klonēt uz savu datoru

### Visos

**1.** Instalējiet git

### Windows

**2.** Spied uz zaļo "code" pogu

**3.** Spied "download zip" pogu

**4.** Unzipo downloadēto failu

### Linux

**2.** Atver termināli (Ctrl + Alt + T)

**2.+** [NEOBLIGĀTI] Ja grib, var pārvietoties uz kādu citu folderi šādi:

```
cd ./<foldera nosaukums>
```

Piemērs:
```
cd ./kaut_kas
```

**3.** Terminālī ir jāievada šis:

```
git clone https://github.com/Gimbrint/tech_school_tic_tac_toe
```

Tas klonēs to repo.

## Pull poga

Var arī parādīties "Pull poga". Tas nozīmē, ka tajā repo kas is githubā ir izmaiņas kas nav tavējā lokālajā klonā. Spiežot tās tiks ieliktas tavējā lokālajā klonā.

## Kā ielikt lietas

### Ja lieto VSCode

**1.** Pa kreisi Spied to figūru zem palielināmā stikla.

**2.** Spied commit. (ja prasa ka nav staged commiti, tad spied "Yes")

**3.** Tagad atverās jauns fails, tajā var pirmajā līnijā ierakstīt ko tu izmainīji un tad var to aizvert ciet, spiežot X pogu blakus nosaukumam.

**4.** Tad parādīsies jauna poga "Sync Changes #". To lūdzu spiediet.

### Ja nelieto

**1.** Atver termināli un ievadi šīs komandas:

```
git commit -am "<izmaiņas>"
git push
```