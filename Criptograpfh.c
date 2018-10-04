#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct element
{
	int key;
	int value;
} element;

typedef struct hash_table
{
	element *table[50];
} hash_table;

hash_table* create_hash_table()
{
	hash_table *new_hash_table = (hash_table*) malloc(sizeof(hash_table));

	int i;

	for ( i = 0; i < 50; i ++ )
	{
		new_hash_table -> table[i] = NULL;
	}

	return new_hash_table;
}

int calc_hash(char key)
{
	if(key == ' ')
	{
		return 'Z' - 'A' + 1;
	}
	return key - 'A';
}

void put(hash_table *ht,  int value)
{
	int h = calc_hash(value);

	while(ht -> table[h] != NULL)
	{
		if (ht -> table[h] != NULL)
		{
			ht -> table[h] -> value == value;
			break;
		}
		h = (h + 1) % 50;
	}

	if(ht -> table[h] == NULL)
	{
		element *new_element = (element*) malloc(sizeof(element));
		new_element -> value = value;
		ht -> table[h] = new_element;
	}
}

int get(hash_table *ht, int key)
{
	return ht -> table[key] -> value;
}

long long unsigned expmod(int x, int exp, int mod)
{ 
  x %= mod;
  long long unsigned resultado = 1 ;
  for ( ; exp > 0; exp --)  resultado = (resultado * x) % mod;
  	return resultado;
}

int inverse(int base,int mod)
{
	for(int i = 0 ;i < mod;i ++)
	{
		if(((i * base) - base) % mod == 0) return i;
	}
}

long  mdc(long m, long n, long *a, long *b)
{
    long d;
    
    if (n == 0) 
    { 
        *a = 1;
        *b = 0; 
        return m;
    }else 
    {
    	long e, f;
        d = mdc (n, m % n, &e, &f);
        *a = f;
        *b = e - f*(m/n);

        return d;
    }
  
}

long long int inverso(long long int ex,long long int phi)
{
	long long int x;
	for(x = 1;x <= phi;x ++)
	{
		if((ex * x) % phi == 1)
			return x;
	}
}

void main()
{
	hash_table* alfa = create_hash_table();
	int i;
	for(i = 'A';i <= 'Z';i ++)
	{
		put(alfa, i);
	}
	put(alfa, ' ');
	int n,e,prime1,prime2,option;
	char message[10000];
	puts("Tell me what you want to do:");
	puts("1. Generate a public key");
	puts("2. Criptograph a message");
	puts("3. Uncriptographed a message");
	scanf("%d", &option);

	if(option == 1)
	{
		puts("Give me 2 prime numbers(they will be your private key):");
		scanf("%d %d", &prime1, &prime2);
		n = prime1 * prime2;
		printf("Give me a number that has mdc = 1 with: ");
		printf("%d\n",(prime1 - 1) * (prime2 - 1));
		scanf("%d", &e);
		FILE *keys = fopen("Public keys.txt","w");
		fprintf(keys,"Public key = %d and %d\n", n, e);
	}

	if(option == 2)
	{
		FILE* cript_message = fopen("cript_message.txt","w+");
		puts("Gimme the public key");
		scanf("%d %d", &n, &e);
		getchar();
		puts("Gimme the uncriptographed message");
		scanf("%[^\n]s", message);
		int i, t = strlen(message);
		for(i = 0; i < t; i ++) fprintf(cript_message,"%lld ",expmod(calc_hash(message[i]), e, n));
			puts("The message was encrypted with sucess!");
	}

	if(option == 3)
	{
		int num;
		char uncriptographed[10000];
		puts("Give me the Private key(2 prime numbers and e):");
		scanf("%d %d %d", &prime1, &prime2, &e);
		n = prime1 * prime2;
		FILE *read = fopen("cript_message.txt","r+");
		rewind (read);
		int i = 0;
		while(!feof(read))
		{
			fscanf(read,"%d ", &num);
			long  d,r;
			d = inverso(e,(prime1 - 1) * (prime2 - 1));
			uncriptographed[i] = get(alfa, expmod(num, d, n));
			i ++;
		}
		printf("The message is \n%s\n", uncriptographed);
	}
}