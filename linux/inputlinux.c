#include <stdio.h>
#include <termios.h>

// Source code by T. Excoffier, May 2016

// La documentation : man termios
// Appeler cette fonction avec 1 pour initialiser l'entrée standard
// Appeler cette fonction avec 0 pour la remettre dans l'état initial
void configure_stdin(int start)
{
  static struct termios original ;
  
  if ( start )
    {
      // Sauvegarde de l'état initial du TTY
      tcgetattr(0, &original) ;
      // En mettant tous les flags à 0, le TTY passe dans le mode RAW
      // dans lequel aucun traitement n'est fait par l'OS,
      // les caractères tapés sont immédiatement envoyés à l'application.
      // Attention : ^H ^C ^D ^Z ^\ ^J ^M perdent donc leur signification.
      struct termios t = {0} ;
      tcsetattr(0, TCSANOW, &t) ;
    }
  else
    tcsetattr(0, TCSANOW, &original) ;
}

int main()
{
  int i = 0, c ;
  printf("Ne fonctionne pas avec de l'UTF-8.\n") ;
  printf("Tapez 'q' pour quitter\n") ;
  configure_stdin(1) ;
  do
    {
      c = getchar() ;
      if ( c == -1 )
	printf("\r(%d)", i++) ;
      else
	printf(" vous avez tapé '%c' (%d)\r\n", c, c) ;
    }
  while( c != 'q' ) ;
  configure_stdin(0) ;
  return 0 ;
}

