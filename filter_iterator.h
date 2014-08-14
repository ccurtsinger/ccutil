#if !defined(CPPGOODIES_FILTER_ITERATOR_H)
#define CPPGOODIES_FILTER_ITERATOR_H

namespace cppgoodies {
  template<class C, class F> class filterer {
  private:
    C _collection;
    F _fn;
  public:
    filterer(C collection, F fn) : _collection(collection), _fn(fn) {}
  
    class iterator {
    private:
      C& _source;
      typename C::iterator _pos;
      F _fn;
    
      void skipFiltered() {
        while(_pos != _source.end() && !_fn(*_pos)) { _pos++; }
      }
    public:
      iterator(C& source, typename C::iterator pos, F fn) : _source(source), _pos(pos), _fn(fn) { 
        skipFiltered();
      }
    
      void operator++() {
        _pos++;
        skipFiltered();
      }
    
      auto operator*() -> decltype(*_pos) {
        return *_pos;
      }
    
      bool operator==(const iterator& other) {
        return _pos == other._pos;
      }
    
      bool operator!=(const iterator& other) {
        return _pos != other._pos;
      }
    };
  
    iterator begin() {
      return iterator(_collection, _collection.begin(), _fn);
    }
  
    iterator end() {
      return iterator(_collection, _collection.end(), _fn);
    }
  };

  template<class C, class F> filterer<C, F> filter(C&& collection, F fn) {
    return filterer<C, F>(std::move(collection), fn);
  }

  template<class C, class F> filterer<C&, F> filter(C& collection, F fn) {
    return filterer<C&, F>(collection, fn);
  }
}

#endif
