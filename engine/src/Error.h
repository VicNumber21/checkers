#ifndef H_ERROR_H
#define H_ERROR_H

#include <tr1/memory>
#include <exception>
#include <string>


namespace Checkers
{
  namespace Engine
  {
    class Error : public std::exception
    {
    public:
      typedef std::tr1::shared_ptr<Engine::Error> Ptr;

    public:
      virtual void raise() const; 
      virtual const char *what() const throw();
      virtual std::string toString() const;
    };
  }
}

#endif //H_ERROR_H
