#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<unistd.h>
#include<vector>

using namespace std;

bool cond_atk(int m, int a, int v) {
  // Checa se eh possivel fazer gol
  if((m+2*a)/(3*1.0) > v) return true;
  return false;
}

bool cond_def(int d, int m, int v) {
  // Checa se eh possivel tomar gol
  if((2*d+m)/(3*1.0) < v) return true;
  return false;
}

void placar(int golsA, int golsB, string A, string B) {
  // Imprime placar
  cout << "Placar: " << A << " " << golsA << " x " << golsB << " " << B << endl << endl;
}

void vence(string C, int golsA, int golsB, string A, string B) {
  // Imprime resultado
  cout << endl << endl;
  placar(golsA,golsB,A,B);
  cout << "O " << C << " venceu!" << endl;
}

void empate(int golsA, int golsB, string A, string B) {
  // Imprime resultado
  cout << endl;
  placar(golsA,golsB,A,B);
  cout << "O jogo terminou em empate!" << endl;
}

void tipo(int type, int i, string A) {
  // Define tipo de gol
  int improvavel = rand()%100;
  if(improvavel==14) cout << "Ih rapaz... O goleirao falhou! Entregou pro " << A << " marcar aos " << i << " minutos!" << endl;
  else {
      if(type < 7 && type > 2) cout << "Gol de escanteio do " << A << " aos " << i << " minutos!" << endl;
      else if(type < 11 && type > 2) cout << "Gol de cabeca do " << A << " aos " << i << " minutos!" << endl;
      else if(type < 14 && type > 2) cout << "Golaco de longe do " << A << " aos " << i << " minutos!" << endl;
      else if(type < 19 && type > 2) cout << "Golaco! Jogada trabalhada do " << A << " aos " << i << " minutos!" << endl;
      else if(type > 2) cout << "Gol de puro talento em jogada individual do " << A << " aos " << i << " minutos!" << endl;
      if(type == 0) cout << "Golaco de falta do " << A << " aos " << i << " minutos!" << endl;
      else if(type < 3) cout << "Gol de penalti do " << A << " aos " << i << " minutos!" << endl;
  }
}

int main(int argc, char const *argv[]) {

  // Garante geracao aleatoria de valores
  srand(time(NULL));

  // Inicializacao de variaveis
  string A,B,verificador,atual,outro;
  int atkA,defA,atkB,defB,da,ma,aa,db,mb,ab,golsA = 0, golsB = 0,definicao,red,posi,lado,
  mudancaA,mudancaB,delay,torc,anulado,lesao,tipolesao,amarelo,qualfalta,velocidade,limite;
  unsigned int microseconds;
  bool blockA,blockB,continua,possivelgolfaltaA,possivelgolfaltaB,retirarA,retirarB,penaltiA,penaltiB,valido;
  vector<int> espacoA;
  vector<int> espacoB;

  continua = true;

  // Definicao de interferencia do delay
  cout << "Escolha a velocidade do jogo de 0 a 7, sendo 0 muito rapido e 7 muito lento. (Recomendado: 2)" << endl;
  cin >> velocidade;
  if(velocidade>7) velocidade = 7;
  if(velocidade<0) velocidade = 0;

  while(continua) {

    // (Re)definindo variaveis
    golsA = 0;
    golsB = 0;
    blockA = false;
    blockB = false;
    espacoA.clear();
    espacoB.clear();
    possivelgolfaltaA = false;
    possivelgolfaltaB = false;
    retirarA = false;
    retirarB = false;
    penaltiA = false;
    penaltiB = false;
    valido = false;

    // Definindo como inserir times
    cout << "Digite 1 caso queira usar times predefinidos. Caso queira usar times personalizados digite 0." << endl;
    cin >> definicao;
    cin.ignore();

    if(!definicao) {

    // Interacao com o usuario para definicao de times
    cout << "Entre com time A:" << endl;
    getline(cin, A);
    cout << "Entre com time B:" << endl;
    getline(cin, B);

    // Capitalizando primeira letra se necessario
    espacoA.push_back(-1);
    espacoB.push_back(-1);
    for(int x = 0; x<A.length(); x++) if(A[x] == 32) espacoA.push_back(x);
    for(int y = 0; y<B.length(); y++) if(B[y] == 32) espacoB.push_back(y);
    for(int w = 0; w < espacoA.size(); w++) if(A[espacoA[w]+1]>96 && A[espacoA[w]+1]<123) A[espacoA[w]+1]-=32;
    for(int z = 0; z < espacoB.size(); z++) if(B[espacoB[z]+1]>96 && B[espacoB[z]+1]<123) B[espacoB[z]+1]-=32;

    // Interacao com o usuario para definicao de forcas
    cout << "Entre com nivel de defesa, meio e ataque do " << A << ":" << endl;
    cin >> da >> ma >> aa;
    cout << "Entre com nivel de defesa, meio e ataque do " << B << ":" << endl;
    cin >> db >> mb >> ab;
    }

    else {

      // Cria array de times e forcas pra cada time
      string nome[] = {"Flamengo", "Vasco", "Corinthians", "Bahia", "Palmeiras", "Botafogo", "Fluminense", "Cruzeiro", "Sao Paulo", "Atl Mineiro",
                    "Atl Paranaense", "Santos", "Gremio", "Vitoria", "Ponte Preta", "Coritiba", "Sport", "Avai", "Atl Goianeense", "Chapecoense",
                    "Brasil","Argentina","Alemanha","Espanha","Franca","Belgica","Holanda","Italia","Barcelona","Real Madrid","Bayern","PSG"};
      int val[] = {74,75,75, 71,72,72, 75,74,75, 70,71,70, 74,72,73, 73,73,72, 72,71,73, 73,73,72, 71,69,73, 73,72,73, 72,71,68, 75,74,72,
                   74,74,75, 67,69,66, 72,69,70, 70,71,70, 70,72,73, 69,68,68, 68,69,64, 71,69,69, 83,90,84, 79,85,89, 88,85,84, 87,84,80,
                   83,87,86, 84,88,84, 80,86,82, 87,79,81, 84,87,88, 85,88,91, 88,86,86, 83,85,90};

      // Mostrando times existentes
      cout << endl << "Escolha quais times utilizar por seus respectivos numeros:" << endl << endl
           << "----------------------------------------------------------------------------------" << endl;
      cout << "|       Flamengo(1) | Vasco(2) | Corinthians(3) | Bahia(4) | Palmeiras(5)        |" << endl;
      cout << "|   Botafogo(6) | Fluminense(7) | Cruzeiro(8) | Sao Paulo(9) | Atl Mineiro(10)   |" << endl;
      cout << "|  Atl Paranaense(11) | Santos(12) | Gremio(13) | Vitoria(14) | Ponte Preta(15)  |" << endl;
      cout << "|   Coritiba(16) | Sport(17) | Avai(18) | Atl Goianeense(19) | Chapecoense(20)   |" << endl;
      cout << "|      Brasil(21) | Argentina(22) | Alemanha(23) | Espanha(24) | Franca(25)      |" << endl;
      cout << "|    Belgica(26) | Holanda(27) | Italia(28) | Barcelona(29) | Real Madrid(30)    |" << endl;
      cout << "|                              Bayern(31) | PSG(32)                              |" << endl;
      cout << "----------------------------------------------------------------------------------" << endl << endl;

      limite = 32;

      // Interacao com o usuario para definicao de times
      int num1,num2;
      while(!valido) {
        cout << "Entre com time A:" << endl;
        cin >> num1;
        if(num1>=1 && num1<=limite) valido = true;
        else cout << "Nao entendi, ";
      }
      valido = false;
      while(!valido) {
        cout << "Entre com time B:" << endl;
        cin >> num2;
        if(num2>=1 && num2<=limite) valido = true;
        else cout << "Nao entendi, ";
      }
      num1--;
      num2--;

      // Recebe os valores de acordo com a escolha dos times
      A = nome[num1];
      B = nome[num2];
      da = val[num1*3];
      ma = val[num1*3+1];
      aa = val[num1*3+2];
      db = val[num2*3];
      mb = val[num2*3+1];
      ab = val[num2*3+2];
    }

    cout << endl << endl;

    cout << "Comeca o jogo! " << A << " x " << B << endl << endl;

    // Cada loop indica um minuto de jogo
    for(int i = 1; i<91; i++) {

      // Ajuste de tempo de execucao
      microseconds = 49000;
      delay = 0;
      if(retirarA) possivelgolfaltaA = false;
      possivelgolfaltaA ? retirarA = true : retirarA = false;
      if(retirarB) possivelgolfaltaB = false;
      possivelgolfaltaB ? retirarB = true : retirarB = false;
      penaltiA = false;
      penaltiB = false;

      // Gerador de valores para definicao de gols
      for(int a1=0; a1<10; a1++) atkA = (rand()*(time(0)/10000))%100;
      for(int a2=0; a2<10; a2++) defA = (rand()*(time(0)/10000))%100;
      for(int a3=0; a3<10; a3++) atkB = (rand()*(time(0)/10000))%100;
      for(int a4=0; a4<10; a4++) defB = (rand()*(time(0)/10000))%100;

      // Torcedor invade campo
      torc = rand()%900;
      if(torc==14) {
        delay = 1;
        cout << "Que situacao! Torcedor revoltado entra em campo pra protestar aos " << i << " minutos, mas e detido a tempo!" << endl << endl;
      }

      // Gol anulado
      anulado = rand()%450;
      if(anulado==196) {
        delay = 1;
        lado = rand()%2;
        atual = lado ? B : A;
        cout << "Bandeirinha atento! O " << atual << " ja ia ampliando o placar aos " << i << " minutos, mas o artilheiro tava na banheira." << endl << endl;
      }

      // Lesao
      lesao = rand()%180;
      if(lesao==100) {
        delay = 1;
        lado = rand()%2;
        tipolesao = rand()%2;
        posi = rand()%8;
        atual = lado ? B : A;
        string posicao[] = {"zagueiro","lateral","lateral","volante","meia","ponta","ponta","centroavante"};
        string arraylesao[] = {"muscular","apos falta grave"};
        cout << "Sai, aos " << i << " minutos, com lesao " << arraylesao[tipolesao] << ", o " << posicao[posi] << " do " << atual << "." << endl << endl;
      }

      // Carto amarelo
      amarelo = rand()%17;
      if(amarelo == 13) {
        delay = 1;
        lado = rand()%2;
        posi = rand()%8;
        string posicao[] = {"zagueiro","zagueiro","lateral","volante","volante","meia","ponta","centroavante"};
        atual = lado ? B : A;
        outro = atual == B ? A : B;
        atual == B ? possivelgolfaltaA = true : possivelgolfaltaB = true;
        cout << "Falta pro " << outro << " aos " << i << " minutos. Amarelo pro " << posicao[posi] << " do " << atual << "." << endl << endl;
      }

      // Expulsao
      red = rand()%180;
      if(red==14) {
        delay = 1;
        posi = rand()%45;
        lado = rand()%2;
        qualfalta = rand()%3;
        atual = lado ? B : A;
        if(!qualfalta) { atual == B ? possivelgolfaltaA = true : possivelgolfaltaB = true; }
        else atual == B ? penaltiA = true : penaltiB = true;
        if(penaltiA) cout << "Penalti pro " << A << "!" << endl;
        else if(penaltiB) cout << "Penalti pro " << B << "!" << endl;

        if(lado==0) {
          if(posi==0) { da*=0.6; cout << "Expulso o goleiro do " << atual << " aos " << i << " minutos!" << endl << endl; }
          else if(posi<9) { da*=0.8; cout << "Expulso o lateral do " << atual << " aos " << i << " minutos!" << endl << endl; }
          else if(posi<21) { da*=0.8; cout << "Expulso o zagueiro do " << atual << " aos " << i << " minutos!" << endl << endl; }
          else if(posi<29) { ma*=0.67; cout << "Expulso o volante do " << atual << " aos " << i << " minutos!" << endl << endl; }
          else if(posi<33) { ma*=0.67; cout << "Expulso o meia do " << atual << " aos " << i << " minutos!" << endl << endl; }
          else if(posi<41) { aa*=0.67; cout << "Expulso o ponta do " << atual << " aos " << i << " minutos!" << endl << endl; }
          else { aa*=0.67; cout << "Expulso o centroavante do " << atual << " aos " << i << " minutos!" << endl << endl; }
        }
        else {
          if(posi==0) { db*=0.6; cout << "Expulso o goleiro do " << atual << " aos " << i << " minutos!" << endl << endl; }
          else if(posi<9) { db*=0.8; cout << "Expulso o lateral do " << atual << " aos " << i << " minutos!" << endl << endl; }
          else if(posi<21) { db*=0.8; cout << "Expulso o zagueiro do " << atual << " aos " << i << " minutos!" << endl << endl; }
          else if(posi<29) { mb*=0.67; cout << "Expulso o volante do " << atual << " aos " << i << " minutos!" << endl << endl; }
          else if(posi<33) { mb*=0.67; cout << "Expulso o meia do " << atual << " aos " << i << " minutos!" << endl << endl; }
          else if(posi<41) { ab*=0.67; cout << "Expulso o ponta do " << atual << " aos " << i << " minutos!" << endl << endl; }
          else { ab*=0.67; cout << "Expulso o centroavante do " << atual << " aos " << i << " minutos!" << endl << endl; }
        }
      }

      // Bonus por falta
      if(possivelgolfaltaA) { atkA-=10; defB+=15; atkB+=15; defA-=10; }
      if(possivelgolfaltaB) { atkB-=10; defA+=15; atkA+=15; defB-=10; }

      // Condicoes para time A fazer gol
      if((cond_atk(ma,aa,atkA) && cond_def(db,mb,defB) && (!cond_atk(mb,ab,atkB) || !cond_def(da,ma,defA))
                                                       && atkA > 0 && atkB > 0 && defA > 0 && defB > 0) || (penaltiA && rand()%5)) {
        delay = 1;
        int type = rand()%18+3;
        if(possivelgolfaltaA) { type = 0; possivelgolfaltaA = false; }
        if(penaltiA) { type = 1; penaltiA == false; }
        tipo(type,i,A);
        golsA++;
        placar(golsA,golsB,A,B);
      }
      else if(penaltiA) cout << "Isolou na cobranca do penalti. Segue " << golsA << " x " << golsB << " o jogo." << endl << endl;

      // Condicoes para time B fazer gol
      if((cond_atk(mb,ab,atkB) && cond_def(da,ma,defA) && (!cond_atk(ma,aa,atkA) || !cond_def(db,mb,defB))
                                                       && atkA > 0 && atkB > 0 && defA > 0 && defB > 0) || (penaltiB && rand()%5)) {
        delay = 1;
        int type = rand()%20+3;
        if(possivelgolfaltaB) { type = 0; possivelgolfaltaB = false; }
        if(penaltiB) { type = 1; penaltiB == false; }
        tipo(type,i,B);
        golsB++;
        placar(golsA,golsB,A,B);
      }
      else if(penaltiB) cout << "Isolou na cobranca do penalti. Segue " << golsA << " x " << golsB << " o jogo." << endl << endl;

      // Mudanca de estrategia
      if(golsA < golsB) {
        if(!blockA) mudancaA = 90 - 10*(golsB-golsA);
        if(mudancaA <= i && !blockA) {
          delay = 1;
          blockA = true;
          da-8 < 1 ? da = 1 : da-=8;
          aa+8 > 99 ? aa = 99 : aa+=8;
          db+8 > 99 ? db = 99 : db+=8;
          ab-8 < 1 ? ab = 1 : ab-=8;
          cout << "Aos " << i << " minutos, com o resultado ruim, o " << A << " se lanca ao ataque, enquanto o " << B << " recua o meio." << endl << endl;
        }
      }
      if(golsA > golsB) {
        if(!blockB) mudancaB = 90 - 10*(golsA-golsB);
        if(mudancaB <= i && !blockB) {
          delay = 1;
          blockB = true;
          db-8 < 1 ? db = 1 : db-=8;
          ab+8 > 99 ? ab = 99 : ab+=8;
          da+8 > 99 ? da = 99 : da+=8;
          aa-8 < 1 ? aa = 1 : aa-=8;
          cout << "Aos " << i << " minutos, com o resultado ruim, o " << B << " se lanca ao ataque, enquanto o " << A << " recua o meio." << endl << endl;
        }
      }

      // Delay
      usleep(velocidade*(microseconds+200000*delay));

    }

    // Mensagem final de placar e resultado
    golsA > golsB ? vence(A,golsA,golsB,A,B) : golsB > golsA ? vence(B,golsA,golsB,A,B) : empate(golsA,golsB,A,B);

    // Checa se usuario deseja continuar no jogo
    cout << endl << "Deseja continuar jogando? (s/n)" << endl;
    cin >> verificador;
    if(verificador[0] == 'n' || verificador[0] == 'N') continua = false;
    cout << endl;
  }
  return 0;
}
