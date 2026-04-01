#pragma once

class Move {
public:
    int fromFile;
    int fromRank;
    int toFile;
    int toRank;
    bool promote;
    bool drop;

    Move(int ff, int fr, int tf, int tr, bool pr = false, bool dr = false)
        : fromFile(ff), fromRank(fr), toFile(tf), toRank(tr),
          promote(pr), drop(dr) {}

    Move()
        : fromFile(0), fromRank(0), toFile(0), toRank(0),
          promote(false), drop(false) {}
};
