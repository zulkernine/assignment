const MyEvent = {
  fire: (key) => {
    window.dispatchEvent(new Event(key));
  },

  on: (key, callback) => {
    window.addEventListener(key, callback);
  },

  remove: (key, callback) => {
    window.removeEventListener(key, callback);
  },
};

export default MyEvent;
