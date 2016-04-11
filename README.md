Code for HC-search for Incremental Parsing
==========================================

This is the code base for our IJCAI 2016 paper.

# Prerequisite

1. cmake (~2.8)
2. git (~1.8)
3. g++ (~4.6 for c++11 features, 4.8 is used in this paper)
4. boost (~1.57)

# Compile

Execute the following command to compile.

```
./configure
make
```

You should find the following executable files:

```
bin/
└── experimental
    ├── hc_depparser_cstep           : Ranker for C-step
    └── hc_depparser_hstep_arcstanda : Parser for H-step
```


# Data format

## Input format for the H-step

The format for input file in the H-step is similar to that of CoNLLX format which contains 8 (or more) columns.
Words in the sentence is counting from `1` and `0` corresponds to the pseudo node.

**NOTE**

Please fill the 5th column with gold standard postag which are used in getting the loss since punctuations
(have the ``'':,. gold postag) are ignored in our loss computation.

## Input format for the C-step

After training the H-step model, you can use `./bin/experimental/hc_depparser_hstep_arcstandard prepare` to generate
the training/testing data for the C-step. The C-step instances are separated by empty space. Each instance has a
header like `#id forms postags oracle-hstep-score output1-hstep-score output2-hstep-score ...`. Following the header
shows the dependency relations for oracle and candidates. Dependency head and relation are separated by `/`. Here is
a example for the C-step input.

```
#id forms postags 3.51423e+09 3.54676e+09 3.54634e+09 ...
1 Influential JJ 2/NMOD 2/NMOD 2/NMOD ...
2 members NNS 10/SUB 10/SUB 10/SUB ...
3 of IN 2/NMOD 2/NMOD 2/NMOD ...
4 the DT 9/NMOD 9/NMOD 9/NMOD ...
5 House NNP 9/NMOD 9/NMOD 9/VMOD ...
```

# Running

## the H-step

1. 20-way jackknifing your dependency training data. For the ith fold, name them as `train.fold$i.conll.train` and `train.fold$i.conll.test`.
2. `./bin/experimental/hc_depparser_hstep_arcstandard learn --train train.fold$i.conll.train --devel devel.conll --model model.hstep.$i --algorithm pa` to train the model for ith fold.
3. `./bin/experimental/hc_depparser_hstep_arcstandard prepare --input train.fold$i.conll.test --output train.cstep.$i --model model.hstep.$i` to prepare the C-step input for ith fold
4. merge `train.cstep.$i` into `train.cstep` to generate the C-step training data.
5. `./bin/experimental/hc_depparser_hstep_arcstandard learn --train train.conll --devel devel.conll --model model.hstep --algorithm pa` to train the overall model.
6. `./bin/experimental/hc_depparser_hstep_arcstandard prepare --input devel.conll --output devel.cstep --model model.hstep` to prepare development input for the C-step.
7. `./bin/experimental/hc_depparser_hstep_arcstandard prepare --input test.conll --output test.cstep --model model.hstep` to prepare test input for the C-step.

## the C-step

1. `./bin/experimental/hc_depparser_cstep learn --train train.cstep --devel devel.cstep --model model.cstep --script "./script/dependency/evaluate.sh en ./devel.conll "` to train the C-step model.
2. `./bin/experimental/hc_depparser_cstep test --input test.cstep --model model.cstep --script "./script/dependency/evaluate.sh chen2014en ./devel.conll "` to test the C-step model.

## note for Chinese dependency

Since the loss computation and evaluation for Chinese dependency is different from English, for Chinese experiments, please set the language option in both the H-step and C-step and the evaluation script.

# Parameters and Get help

The provided parameters include:

1. the H-step: `--neg-sample` the negative sample selection `strategy`, `baseline`, `best`, or `worst`.
2. the C-step: `--ranker` the ranking strategy, `fine` or `coars`.
3. the H-step and C-step: `language` to specify the language.

Use `--help` option in the executable binaries to get more help. Or write to Yijia Liu <oneplus.lau@gmail.com>.
