#include<iostream>
#include<string>
#include<list>
#include<math.h>

#include <QDebug>


using namespace std;


/*
 smth was inserted here
 */




struct oper_stack_node{
    char oper;
    int priority;
    oper_stack_node* next;
    oper_stack_node* prev;
    oper_stack_node(char a, int p, oper_stack_node* p_n, oper_stack_node* n_n)
    { oper=a;
      priority=p;
      next = n_n;
      prev = p_n;
    }
};


struct expr_stack_node{
    string expr;
    int priority;
    expr_stack_node* next;
    expr_stack_node* prev;
    expr_stack_node(string s, int p, expr_stack_node* p_n, expr_stack_node* n_n)
    { expr=s;
      priority = p;
      next = n_n;
      prev = p_n;
    }
};



int priority(char oper)
{
    switch (oper){
        case '(': return 0; break;
        case ')': return 1; break;
        case '+': return 2; break;
        case '-': return 2; break;
        case '*': return 3; break;
        case '/': return 3; break;
        case '^': return 4; break;
        default : return -1;
    }
}


string ipn(string str)
{

  // str = "(:A1+:B1*:H1-:F1)*(:C1+:D1)-:E1";

   str = "(110+120*130-140)*(210+220)-310";

  // str = "(11+12*13-14)*(21+22)-31";

    oper_stack_node* oper_head=NULL;
    expr_stack_node* expr_head=NULL;
    oper_stack_node* oper_tail=NULL;
    expr_stack_node* expr_tail=NULL;


    int i=0;
    string operant="";
    int last_prior=0;


    while( str[i] != '\0' && i<17)
    {
// || str[i] == ')'
        if( str[i] == '('  ||  str[i] == '+' || str[i] == '-'  || str[i] == '*'  || str[i] == '/' || str[i] == '^')
        {
            if(expr_head != NULL)
            { expr_stack_node* expr_curr_node = expr_head;
              while( expr_curr_node->next != NULL && expr_curr_node->priority < last_prior )  expr_curr_node = expr_curr_node->next;

              if(expr_curr_node->next != NULL)
              {
                  expr_stack_node* tmp = new expr_stack_node(operant, last_prior, expr_curr_node->prev, expr_curr_node);
                  expr_curr_node->prev->next = tmp;
                  expr_curr_node->prev = tmp;
              }else
              {   expr_curr_node->next = new expr_stack_node(operant, last_prior,  expr_curr_node, NULL);
                  expr_tail = expr_curr_node->next;

              }

            }else
            {
              expr_head = new expr_stack_node(operant, last_prior, NULL, NULL);
              expr_tail = expr_head;
            }
//  check for   div  mod
            operant = "";


            int prior = priority(str[i]);
            last_prior=prior;
            if(expr_tail->priority < prior) expr_tail->priority = prior;


            if(oper_head == NULL)
            {   oper_head = new oper_stack_node(str[i], prior, NULL, NULL);
                oper_tail = oper_head;
            }else
            {   oper_stack_node* oper_curr_node = oper_head;
                while ( oper_curr_node->priority < prior && oper_curr_node->next != NULL)  oper_curr_node = oper_curr_node->next;

                if( oper_curr_node->next != NULL)
                {
                    oper_stack_node* tmp = new oper_stack_node(str[i], prior, oper_curr_node->prev, oper_curr_node);
                    oper_curr_node->prev->next=tmp;
                    oper_curr_node->prev = tmp;
                } else
                {   oper_curr_node->next = new oper_stack_node(str[i], prior,  oper_curr_node, NULL);
                    oper_tail = oper_curr_node->next;
                }
            }

            while(oper_head->prev != NULL) oper_head = oper_head->prev;
            while(oper_tail->next != NULL) oper_tail = oper_tail->next;




        }else
        {

             if(str[i] == ')' )
             {

                 if(expr_head != NULL)
                 { expr_stack_node* expr_curr_node = expr_head;

                   while( expr_curr_node->next != NULL && expr_curr_node->priority < last_prior)  expr_curr_node = expr_curr_node->next;

                   expr_stack_node* tmp = new expr_stack_node(operant, last_prior, expr_curr_node->prev, expr_curr_node);
                //   expr_curr_node->prev->next = tmp;
                   expr_curr_node->prev = tmp;

                 }else
                 {
                   expr_head = new expr_stack_node(operant, last_prior, NULL, NULL);
                   expr_tail = expr_head;
                 }


     //  check for   div  mod


                 operant = "";


                 oper_stack_node* oper_curr_node = oper_tail;

                 while(oper_curr_node->oper != '(' && oper_curr_node != NULL)
                 {

                     oper_stack_node* tmp = oper_tail;
                     oper_tail = oper_tail->prev;
                     oper_tail->next = NULL;

                     free(tmp);

                     oper_curr_node = oper_curr_node->prev;

                 }



// Do what you have to do when ')' happend






             }else
             {

                operant+=str[i];

             }
/**/

        }
        i++;
    }


/**/
    oper_stack_node* oper_curr_node;

    while(oper_head->prev != NULL) oper_head=oper_head->prev;

    oper_curr_node = oper_head;
    i=0;
    str="";

    while(oper_curr_node != NULL)
    {   str += oper_curr_node->oper;
        oper_curr_node = oper_curr_node->next;
        i++;
    }
    str[i] ='\0';


/*
    str="";
    */
    expr_stack_node* expr_curr_node = expr_head;

    while(expr_curr_node != NULL)
    {   str += expr_curr_node->expr ;
        expr_curr_node = expr_curr_node->next ;

    }

    return str;
}












/*
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
*/










bool is_integer_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}



struct node
{
  string (*ptr_function)(node* , node* );

  node* l_node;
  node* r_node;
  string expression;
  node(string s){
    expression = s;
    l_node = NULL;
    r_node =NULL;

    qDebug() << "\n node constructor got: " << QString(s.c_str());
  }
  void clean(){
      if(l_node != NULL) { l_node->clean(); delete l_node;}

      if(r_node != NULL) { r_node->clean(); delete r_node;}
  }
};


string addition(node* , node* );
string subtraction(node* , node* );
string multiplication(node* , node* );
string division(node* , node* );

string div(node* , node* );
string mod(node* , node* );

string power(node* , node* );


string expr_analyse(node* curr_node)
{
  string expr = curr_node->expression;
  // (1) find operation + - div mod /
  string l_expr, r_expr;
  /* the ampersand is actually optional */
  int i=0; int k=0;
  while( expr[i] != '\0' )
  { if(expr[i] == '+')
    { curr_node->ptr_function = &addition;
      k=i;
      break;
    }else{
          if(expr[i] == '-')
              { curr_node->ptr_function = &subtraction;
                k=i;
                break;
              }else{
                        if(expr[i] == '*')
                        {   curr_node->ptr_function = &multiplication;
                            k=i;
                            break;
                        }else{
                            if(expr[i] == '/')
                            {   curr_node->ptr_function = &division;
                                k=i;
                                break;
                            }
                        }



                    }


          }
    i++;

  }
  if(k){
    l_expr = std::string(expr, 0, k); // initial_str,  first_pos, length_of_sub_string
    r_expr = std::string(expr, k+1, expr.length()-k-1);
   }else{
      if(! is_integer_number(expr) ) {
          return "1";
      }

      else {
          return expr;
      }

  }

  node* l_node = new node(l_expr);
  node* r_node = new node(r_expr);

 // qDebug()<<" doing operation on "<<QString(l_expr.c_str())<<" and "<<QString(r_expr.c_str());


  // expr_analyse( ... )

  return  curr_node->ptr_function(l_node, r_node);
}

string addition(node* l_node, node* r_node)
{
  string l_expr =  expr_analyse(l_node);
  string r_expr = expr_analyse(r_node);
  int sum = std::stof(l_expr) +  std::stof(r_expr);
  return std::to_string(sum);
}

string subtraction(node* l_node, node* r_node)
{
  string l_expr =  expr_analyse(l_node);
  string r_expr = expr_analyse(r_node);
  int result = std::stof(l_expr) -  std::stof(r_expr);
  return std::to_string(result);
}

string multiplication(node* l_node, node* r_node)
{
  string l_expr =  expr_analyse(l_node);
  string r_expr = expr_analyse(r_node);
  int result = std::stof(l_expr) *  std::stof(r_expr);
  return std::to_string(result);
}

string div(node* l_node, node* r_node)
{
  string l_expr =  expr_analyse(l_node);
  string r_expr = expr_analyse(r_node);
  int div = (int) (std::stof(l_expr) /  std::stof(r_expr));
  return std::to_string(div);
}

string division(node* l_node, node* r_node)
{
  string l_expr =  expr_analyse(l_node);
  string r_expr = expr_analyse(r_node);
  float div = (float) (std::stof(l_expr) /  std::stof(r_expr));
  return std::to_string(div);
}

string mod(node* l_node, node* r_node)
{
  string l_expr =  expr_analyse(l_node);
  string r_expr = expr_analyse(r_node);
  int div = (int) (std::stoi(l_expr) %  std::stoi(r_expr));
  return std::to_string(div);
}

string power(node* l_node, node* r_node)
{
  string l_expr = expr_analyse(l_node);
  string r_expr = expr_analyse(r_node);
  float result = pow( std::stof(l_expr) ,  std::stof(r_expr) );
  return std::to_string(result);
}

string start_expr_analyse(string str)
{
    qDebug() <<  "Started to analyse "<<QString(str.c_str());
    node * root = new node(str);

    string result =  expr_analyse(root);



  // root->clean();
  // delete root;
   return result;
}
