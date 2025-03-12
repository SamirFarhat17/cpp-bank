namespace Recording {

    template<typename T>
    class Writer {
        private: 
            int id;
        protected:
            void writeLine(T bankObj);
            void calculateLine(T bankObj);
    };

    template<typename T>
    class Reader {
        private:
            int id;
        protected:
            void readLine();
            void calculateRead(T bankObj);
    };

};