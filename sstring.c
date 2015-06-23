
#include "sstring.h"
#include <stdlib.h>      /* Use realloc. */

/* Checking. */
int sstring_isok(sstring *this)
{
   if (this != (sstring *)NULL)
      if (this->error(this) == SS_OK) 
         return TRUE;
      return this->error(this);
   
   return FALSE;
}

int sstring_array_isok(sstring *this[], int limit)
{
   int control [2] = { 0, 0 };

   if (limit > 0)
   {
      for (control[0] = 0; control[0] <= limit; control[0]++)
         if (this[control[0]] != (sstring *)NULL)
            if (this[control[0]]->error(this[control[0]]) == SS_OK) 
               control[1]++;               
      
      if (control[1] == limit) return TRUE;
   }

   return FALSE;
}

/* Constructor. */
sstring *new_sstring (const unsigned char *string_initialization)
{
   sstring *string = { 0 };

   if (string = (sstring *)_alloc(string, sizeof(sstring)))
   {
      _set(string, 0, sizeof(sstring));

      /* Default values. */
      string->_last_error     = SS_UNKNOWN;
      string->_string_value   = NULL;
      string->_string_length  = 0;

      /* Public. */
      string->error           = _error;
      string->string          = _string;
      string->length          = _length;
      string->value           = _value;
      string->delete          = _delete;
      string->concat          = _concat;
      string->zero            = _zero;
      string->compare         = _compare;
      string->search          =  _search;
      string->set_value       = _set_value;
      string->replace         = _replace;
      string->tolower         = __tolower;
      string->toupper         = __toupper;
      string->position        = _position;
      string->is_char         = _is_char;
      string->is_numeric      = _is_numeric;
      string->revert          = _revert;

      /* Private. */
      string->_len            = _len;
      string->_set            = _set;
      string->_copy           = _copy;
      string->_alloc          = _alloc;
      string->_clear          = _clear;

      /* Checking 'Is OK'. */
      if (string->error     && string->string  && string->length  && string->value    && string->delete    &&
         string->concat     && string->zero    && string->compare && string->search   && string->set_value &&
         string->replace    && string->tolower && string->toupper && string->position && string->is_char   &&
         string->is_numeric && string->revert  &&
         string->_len       && string->_set    && string->_copy   && string->_alloc   && string->_clear)
      {
         string->_last_error = SS_OK;

         /* Initialization. */
         if (string_initialization != (char *)NULL)
            string->value(string, string_initialization);

         return string;
      }

      _clear(string, sizeof(sstring));
   }

   return (sstring *)NULL;
}

/* Functions. (Public) */
unsigned int _error(struct sstring *this)
{
   return this->_last_error;
}

unsigned char *_string (struct sstring *this)
{
   return this->_string_value;
}
   
unsigned int _length(struct sstring *this)
{
   return this->_string_length;
}

unsigned char *_value(sstring *this, const unsigned char *string)
{
   unsigned char *pointer = NULL;
   unsigned int length = 0;
   this->_last_error = SS_UNKNOWN;

   if (length = this->_len(string))
   {
      if ((this->_string_value = (unsigned char *)this->_alloc(this->_string_value,
         (length * sizeof(char)) + 1)) != NULL)
      {
         this->_set((void *)this->_string_value, '\0', (length * sizeof(char)) + 1);
         this->_copy((void *)this->_string_value, (void *)string, length);
         this->_last_error = SS_SET_VALUE;
         this->_string_length = length;
		 return this->_string_value;
      }
   }

   return pointer;
}

void _delete(sstring *this)
{
   this->_last_error = SS_UNKNOWN;

   if (this->_string_value && this->_string_length)
   {
      this->_clear(this->_string_value, this->_string_length);
      this->_last_error = SS_DELETED;
      this->_string_length = 0;
   }
   else 
      this->_last_error = SS_INVALID_BUFFER;
}

unsigned char *_concat(sstring *this, const unsigned char *string)
{
   unsigned char *pointer = NULL;
   int length = 0, index = 0;
   this->_last_error = SS_UNKNOWN;

   if (this->_string_length > 0 && this->_string_value && string)
   {
      if (length = this->_len(string))
      {
         if ((this->_string_value = (unsigned char *)this->_alloc(this->_string_value, 
            ((this->_string_length + length) * sizeof(char)) + 1)) != NULL)
         {
            for (index = 0; index < length; index++)
               this->_string_value[this->_string_length + index] = string[index];
            
            this->_string_value[this->_string_length + index] = '\0';
            this->_string_length += index;
            
            this->_last_error = SS_CONCATENATED;
            return this->_string_value;
         }
      }
   }
   else
      this->_last_error = SS_INVALID_BUFFER;

   return pointer;
}

void _zero(sstring *this)
{
   this->_last_error = SS_UNKNOWN;

   if (this->_string_value && this->_string_length)
   {
      this->_set(this->_string_value, '\0', this->_string_length);
      this->_last_error = SS_ZEROED;
   }
   else
      this->_last_error = SS_INVALID_BUFFER;
}

unsigned int _compare(sstring *this, const unsigned char *string)
{
   int control = 0;
   this->_last_error = SS_UNKNOWN;

   if (string && this->_string_value && this->_string_length)
   {
      while (string[control] == this->_string_value[control])
         control++;

      if ((control - 1) == this->_string_length && (control - 1) == this->_len(string))
         this->_last_error = SS_EQUAL;
      else
         this->_last_error = SS_NOT_EQUAL;
   }
   else
      this->_last_error = SS_INVALID_BUFFER;

   return this->_last_error;
}

unsigned char *_search(sstring *this, const unsigned char *delimiter)
{
   unsigned char *pointer = NULL;
   int position;

   if (delimiter && this->_string_value && this->_string_length)
   {
      if (pointer = _search_ex(this->_string_value, delimiter, &this->_last_error, &position))
         return pointer;
   }
   else
      this->_last_error = SS_INVALID_BUFFER;

   return pointer;
}

unsigned char *_set_value(sstring *this, const unsigned char *string, unsigned int startup)
{
   unsigned char *pointer = NULL;
   int length = 0, index = 0;
   this->_last_error = SS_UNKNOWN;

   if (string && this->_string_value && this->_string_length)
   {
      length = this->_len(string);
      if ((startup + length) - 1 < this->_string_length)
      {
         for (index = 0; index < length; index++)
            this->_string_value[startup + index] = string[index];
         
         this->_last_error = SS_STRING_COPIED;
         return &this->_string_value[startup];
      }
      else
         this->_last_error = SS_VERY_LARGE_STRING;
   }

   return pointer;
}

unsigned char *_replace(sstring *this, const unsigned char *old_string, const unsigned char *new_string)
{
   return (unsigned char *)NULL;
}

unsigned char *__tolower(sstring *this)
{
   unsigned char *pointer = NULL;
   unsigned int control [3] = { 0, 0, 0 };
   this->_last_error = SS_UNKNOWN;

   if (this->_string_value && this->_string_length)
   {
      if (_str_to_lower_and_upper(this->_string_value, this->_string_length, 65, 97, 91))
         return this->_string_value;

      this->_last_error = SS_TOLOWER_EXECUTED;
   }
   else
      this->_last_error = SS_INVALID_BUFFER;

   return pointer;
}

unsigned char *__toupper(sstring *this)
{
   unsigned char *pointer = NULL;
   unsigned int control [3] = { 0, 0, 0 };
   this->_last_error = SS_UNKNOWN;

   if (this->_string_value && this->_string_length)
   {
      if (_str_to_lower_and_upper(this->_string_value, this->_string_length, 97, 65, 123))
         return this->_string_value;

      this->_last_error = SS_TOUPPER_EXECUTED;
   }
   else
      this->_last_error = SS_INVALID_BUFFER;

   return pointer;
}

unsigned int _position(sstring *this, const unsigned char *delimiter)
{
   unsigned int position = 0;
   this->_last_error = SS_UNKNOWN;

   if (this->_string_value && this->_string_length && delimiter)
   {
      if (_search_ex(this->_string_value, delimiter, &this->_last_error, &position))
         return position;

      this->_last_error = SS_POSITION_FOUND;
   }
   else
      this->_last_error = SS_INVALID_BUFFER;

   return position;
}

unsigned int _is_char(const char _char)
{
   unsigned int control [2] = { 0, 0 };

   if (_char)
      for (control[0] = 97, control[1] = 65; control[1] != 91; control[0]++, control[1]++)
         if (_char == (char)control[0] || _char == (char)control[1])
            return TRUE;

   return FALSE;
}

unsigned int _is_numeric(const char _char)
{
   unsigned int control = 0;

   if (_char)
      for (control = 48; control != 58; control++)
         if (_char == (char)control || _char == (char)control)
            return TRUE;

   return FALSE;
}

unsigned char *_revert(sstring *this)
{
   unsigned char *pointer = NULL;
   unsigned int control [2] = { 0, 0 };
   unsigned int length = 0;
   unsigned char *temporary = NULL;

   if (this->_string_value && this->_string_length)
   {
      if (temporary = (unsigned char *)_alloc(temporary, (this->_string_length * sizeof(char)) + 1))
      {
         this->_set((void *)temporary, '\0', (this->_string_length * sizeof(char)) + 1);
         control[0] = (this->_string_length - 1); 

         for (control[1] = 0; control[0] < this->_string_length; control[0]--, control[1]++)
            temporary[control[1]] = this->_string_value[control[0]];
         
         if (_len(temporary) == this->_string_length)
         {
            this->_copy((void *)this->_string_value, (void *)temporary, this->_string_length);
            this->_last_error = SS_STRING_REVERTED;
         }

         _clear(temporary, this->_string_length);
      }

      return this->_string_value;
   }

   return pointer;
}

/* Functions. (Private) */
unsigned int _len(const unsigned char *string)
{
   unsigned int length = 0;

   while (*string++)
      length++;

   return length;
}

void *_set(void *pointer, unsigned int value, unsigned int length)
{
   unsigned char *_pointer = (unsigned char *)pointer;

   while (length > 0)
   {
      *_pointer = value;
      _pointer++;
      length--;
   }

   return (void *)_pointer;
}

void *_copy(void *destination, const void *source, unsigned int length)
{
   unsigned char *pointer_a = (unsigned char *)destination;
   unsigned char *pointer_b = (unsigned char *)source;

   while (length--)
      *pointer_a++ = *pointer_b++;

   return destination;
}

void *_alloc (void* pointer, unsigned int length)
{
   void *_pointer;

   if ((_pointer = realloc(pointer, length)) != NULL)
      return _pointer;

   return NULL;
}

void _clear(void *pointer, unsigned int length)
{
   _set(pointer, '\0', length);
   _alloc(pointer, 0);
}

unsigned char *_search_ex(unsigned char *string, const unsigned char *delimiter, unsigned int *last_error, unsigned int *position)
{
   unsigned char *pointer = NULL;
   int control [4] = { 0, 0, 0, 0 };

   if (delimiter && string)
   {
      control[0] = _len(delimiter);
      pointer = string;

      for (;*pointer++; control[3]++)
      {
         for (control[1] = 0; control[1] <= control[0]; control[1]++)
            if (string[control[3] + control[1]] == delimiter[control[1]])
               control[2]++;
            else 
               break;

         if (control[2] == control[0]) 
         {
            *last_error = SS_STRING_FOUND;
            *position = control[3];
            break;
         }
         else
            *last_error = SS_STRING_NOT_FOUND;
      }

      return pointer - 1;
   }

   return pointer;
}

unsigned char *_str_to_lower_and_upper(unsigned char *string, const unsigned int length,
   const unsigned int start_a, const unsigned int start_b, const unsigned int delimiter)
{
   unsigned int control [3] = { 0, 0, 0 };

   if (string && _len(string))
   {
      for (control[0] = 0; control[0] <= _len(string); control[0]++)
         for (control[1] = start_a, control[2] = start_b;
            control[1] != delimiter;
            control[1]++, control[2]++)
         {
            if (string[control[0]] == (char)control[1])
               string[control[0]] = (char)control[2];
         }

         return string;
   }

   return (unsigned char *)NULL;
}
