//
// Created by bparsy on 4/28/20.
//

#ifndef CELLS_CODON_H
#define CELLS_CODON_H

#include <memory>
#include <utility>
#include <vector>
#include <functional>


class Codon {
protected:
    Codon() = default;
};

using codon_ptr = std::shared_ptr<Codon>;
using codons = std::vector<codon_ptr>;


#endif //CELLS_CODON_H
