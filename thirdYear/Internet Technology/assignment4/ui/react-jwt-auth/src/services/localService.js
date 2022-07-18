const MyStorage = {
  getString: (key) => {
    return localStorage.getItem(key);
  },

  setString: (key, val) => {
    return localStorage.setItem(key, val);
  },

  remove: (key) => {
    localStorage.removeItem(key);
  },

  addToSet: (key, val) => {
    const _t = MyStorage.getString(key);
    console.log(_t);
    let x = _t != null ? new Set(_t) : new Set([]);
    x.add(val);
    console.log(val, x);
    MyStorage.setString(key, JSON.stringify(x));
  },

  getSet: (key) => {
    const _t = MyStorage.getString(key);
    let x = _t != null ? new Set(_t) : new Set([]);
    return x;
  },
};

export default MyStorage;
