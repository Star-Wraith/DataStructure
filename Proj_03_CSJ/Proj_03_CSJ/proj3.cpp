

#include <stdio.h>
#include <string.h>

#define MAX_TERM 101 //ÃÖ´ë Â÷¼ö 100

#define PROB 1

#if PROB == 1
typedef struct polynomial {
	int degree;
	int coef[MAX_TERM];
}POLY;

void printPoly(const char* pszdata, POLY poly)
{
	int max_poly = poly.degree;
	int i = 0;
	printf("%s=  ", pszdata);
	while (poly.degree >= 0) {
		
		if (max_poly == poly.degree) {
			printf("%dx^%d\t", poly.coef[i], poly.degree);
		}
		else {
			if (poly.coef[i] >= 0) {
				printf("+%dx^%d\t", poly.coef[i], poly.degree);

			}
			else {
				printf("%dx^%d\t", poly.coef[i], poly.degree);
			}
		}


		--poly.degree;
		++i;
	}
	putchar('\n');
}


POLY addPoly(POLY a_poly, POLY b_poly)
{
	POLY result{};
	int a_i = 0;	// a_poly ÀÇ coefÀÎµ¦½º
	int b_i = 0;	// b_poly ÀÇ coefÀÎµ¦½º
	int r_i = 0;	// result ÀÇ coefÀÎµ¦½º
	int max_degree = 0;
	if (a_poly.degree >= b_poly.degree) {
		result.degree = a_poly.degree;
		max_degree = result.degree;
	}
	else {
		result.degree = b_poly.degree;
		max_degree = result.degree;
	}
	while (a_poly.degree >= 0 && b_poly.degree >= 0) {

		if (a_poly.degree > b_poly.degree) {
			result.coef[r_i] = a_poly.coef[a_i];
			++a_i;
			++r_i;
			--a_poly.degree;
		}
		else if (a_poly.degree == b_poly.degree) {
			result.coef[r_i] = a_poly.coef[a_i] + b_poly.coef[b_i];
			++a_i;
			++b_i;
			++r_i;
			--a_poly.degree;
			--b_poly.degree;
		}
		else { // a_poly.degree < b_poly.degree
			result.coef[r_i] = b_poly.coef[b_i];
			++b_i;
			++r_i;
			--b_poly.degree;
		}
	}

	return result;
	
}

POLY mulPoly(POLY a_poly, POLY b_poly)
{
	
	POLY c_poly; // °ö¼À °ªÀ» ¹Ş¾Æ ¹İÈ¯ÇØ ÁÙ ±¸Á¶Ã¼
	c_poly.degree = a_poly.degree + b_poly.degree; 

	int a_poly_degree = a_poly.degree;
	int b_poly_degree = b_poly.degree;
	int coef_index = 0;

	memset(c_poly.coef, 0, sizeof(int) * MAX_TERM);
	for (int i = 0; i <= a_poly_degree; ++i) {

		
		for (int j = 0; j <= b_poly_degree; ++j) {
			 coef_index = c_poly.degree - (a_poly.degree + b_poly.degree);
			 if (c_poly.coef[coef_index] == 0) {
				 c_poly.coef[coef_index] = a_poly.coef[i] * b_poly.coef[j];
			 }
			 else {
				 c_poly.coef[coef_index] += a_poly.coef[i] * b_poly.coef[j];
			 }
			 --b_poly.degree;
			
		}
		b_poly.degree = b_poly_degree;
		--a_poly.degree;
	}

	return c_poly;
}

int main(void) {
	POLY a = { 5, {3, 0, 4, -2, 1, 7} }; // a(x) = 3x5 + 4x3 - 2x2 + 1x + 7
	POLY b = { 3, {4, 2, -6, -3} }; // b(x) = 4x3 + 2x2 - 6x - 3
	POLY c, d; //for result
	printPoly("a(x)", a);
	printPoly("b(x)", b);
	c = addPoly(a, b);
	printPoly("c(x) = a(x) + b(x) ", c);
	d = mulPoly(a, b);
	printPoly("d(x) = a(x) x b(x) ", d);
	return 0;
}
#elif PROB == 2


typedef struct term { int coef; int exp; } TERM;
typedef struct polynomial {
	int num_of_terms;
	TERM terms[MAX_TERM];
}POLY;

void printPoly(const char* pszdata, POLY poly)
{
	int coef_first = 0;
	int i = 0;
	printf("%s=  ", pszdata);
	while (poly.num_of_terms >= 0) {

		if (coef_first == 0) {
			printf("%dx^%d\t", poly.terms[i].coef, poly.terms[i].exp);
			++coef_first;
		}
		else {
			if (poly.terms[i].coef >= 0) {
				printf("+%dx^%d\t", poly.terms[i].coef, poly.terms[i].exp);

			}
			else {
				printf("%dx^%d\t", poly.terms[i].coef, poly.terms[i].exp);
			}
		}
		if (poly.terms[i].exp == 0) {
			break;
		}
		--poly.num_of_terms;
		++i;
	}
	putchar('\n');
}

POLY addPoly(POLY a_poly, POLY b_poly)
{
	POLY result{};
	int a_i = 0;	// a_poly ÀÇ termsÀÎµ¦½º
	int b_i = 0;	// b_poly ÀÇ termsÀÎµ¦½º
	int r_i = 0;	// result ÀÇ termsÀÎµ¦½º
	int count = 0;
	while (a_poly.num_of_terms > 0 && b_poly.num_of_terms > 0) {

		if (a_poly.terms[a_i].exp > b_poly.terms[b_i].exp) {
			result.terms[r_i].coef = a_poly.terms[a_i].coef;
			result.terms[r_i].exp = a_poly.terms[a_i].exp;
			++a_i;
			++r_i;
			--a_poly.num_of_terms;
			++count;
		}
		else if (a_poly.terms[a_i].exp == b_poly.terms[b_i].exp) {
			if (a_poly.terms[a_i].coef + b_poly.terms[b_i].coef != 0) {
				result.terms[r_i].coef = a_poly.terms[a_i].coef + b_poly.terms[b_i].coef;
				result.terms[r_i].exp = a_poly.terms[a_i].exp;
				++r_i;
				++count;
			}
			else {

			}
			++a_i;
			++b_i;
			--a_poly.num_of_terms;
			--b_poly.num_of_terms;
		}
		else { // a_poly.terms[a_i].exp < b_poly.terms[b_i].exp
			result.terms[r_i].coef = b_poly.terms[b_i].coef;
			result.terms[r_i].exp = a_poly.terms[b_i].exp;
			++b_i;
			++r_i;
			--b_poly.num_of_terms;
			++count;
		}
	}

	result.num_of_terms = count;
	return result;

}

POLY mulPoly(POLY a_poly, POLY b_poly)
{

	POLY c_poly{}; // °ö¼À °ªÀ» ¹Ş¾Æ ¹İÈ¯ÇØ ÁÙ ±¸Á¶Ã¼

	int coef_index = 0;
	c_poly.num_of_terms = a_poly.terms[0].exp + b_poly.terms[0].exp;
	for (int i = 0; i <= a_poly.num_of_terms; ++i) {

		for (int j = 0; j <= b_poly.num_of_terms; ++j) {
			coef_index = c_poly.num_of_terms - (a_poly.terms[i].exp + b_poly.terms[j].exp);
			if (c_poly.terms[coef_index].coef == 0) {
				c_poly.terms[coef_index].coef = a_poly.terms[i].coef * b_poly.terms[j].coef;
				c_poly.terms[coef_index].exp  = a_poly.terms[i].exp + b_poly.terms[j].exp;

			}
			else {
				c_poly.terms[coef_index].coef += a_poly.terms[i].coef * b_poly.terms[j].coef;
			}

		}

	}

	return c_poly;
}


int main(void) {
	POLY a = { 5, {3,5, 4,3, -2,2, 1,1, 7,0} }; // a(x) = 3x5 + 4x3 - 2x2 + 1x + 7
	POLY b = { 4, {4,3, 2,2, -6,1, -3,0} }; // b(x) = 4x3 + 2x2 - 6x - 3
	POLY c, d; //for result
	printPoly("a(x)", a);
	printPoly("b(x)", b);
	c = addPoly(a, b);
	printPoly("c(x) = a(x) + b(x) ", c);
	d = mulPoly(a, b);
	printPoly("d(x) = a(x) x b(x) ", d);
	return 0;
}

#endif