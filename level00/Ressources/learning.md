# Learning

![](./protections.png)



#### RELRO (Relocation Read-Only)

Le **Partial RELRO** protege les sections `.data` et `.bss` lors de l'execution.

Le **Full RELRO** quant a lui protege egalement la section `.got` de la **PLT** (Procedure Linkage Table), utilisee pour resoudre les adresses des fonctions a l'execution.



#### STACK CANARY

Les "canary" servent a **proteger la Stack contre les Buffer Overflows**.

Il s'agit d'une valeur placee entre les variables locales et les adresses de retour.

Si un Canary est modifie, le programme le detecte est stoppe l'execution.



#### NX (No Execute)

**NX empeche l'execution de code** dans les sections de la memoire indiquee tel que la **Stack** ou la **Heap**.

Cette protection empeche donc les attaques de type Shellcodes.



#### PIE (Position Independent Executable)

PIE est un flag de compilation rendent l'executable "independant de la position memoire", plus precisemment, le binaire sera compatible avec l'**ASLR**.

**ASLR** (Address Space Layout Randomization) est une technique de sécurité utilisée pour rendre les attaques d'exploitation plus difficiles. Les adresses memoire du programme ne seront pas fixes mais aleatoires a chaque execution.

**ATTENTION:** PIE n'est utile que si l'**ASLR** (Address Space Layout Randomization) est actif sur le systeme Hote.

> cat /proc/sys/kernel/randomize_va_space
>
> * **0** : ASLR est désactivé.
> * **1** : ASLR est partiellement activé (pile, tas et bibliothèques).
> * **2** : ASLR est entièrement activé

De maniere plus detaillee, ASLR modifie de manière aléatoire les adresses de mémoire utilisées par les composants d'un programme, tels que :

* La **pile** (stack).
* Le **tas** (heap).
* Les bibliothèques partagées (comme les `.so` sur Linux).
* Le segment **bss/data/code**.
* L'espace mémoire de l'exécutable principal (s'il est compilé avec PIE).

*Si PIE n'est pas present, cela signifie que l'ASLR **ne protège pas le code du programme lui-même** , et les adresses du code restent prédictibles.*



#### RPATH / RUNPATH

Ces champs définissent les chemins de recherche des bibliothèques dynamiques nécessaires à l'exécution du binaire.

L'absence de ces chemins est une bonne pratique, car leur présence peut être exploitée par des attaques comme **l'injection de bibliothèques malveillantes**.
