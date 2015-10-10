/*
 * modelfactorymixlen.h
 *
 *  Created on: Sep 2, 2015
 *      Author: minh
 */


#include "modelfactory.h"

class ModelFactoryMixlen : public ModelFactory {

public:

	/**
		constructor
		create substitution model with possible rate heterogeneity. Create proper class objects
		for two variables: model and site_rate. It takes the following field of params into account:
			model_name, num_rate_cats, freq_type, store_trans_matrix
		@param params program parameters
		@param tree associated phylogenetic tree
	*/
	ModelFactoryMixlen(Params &params, PhyloTree *tree, ModelsBlock *models_block);

	/**
		optimize model parameters and tree branch lengths
		@param fixed_len TRUE to fix branch lengths, default is false
		@return the best likelihood 
	*/
	virtual double optimizeParameters(bool fixed_len = false, bool write_info = true,
                                      double logl_epsilon = 0.1, double gradient_epsilon = 0.001);


    /**
     * @return #parameters of the model + # branches
     */
    virtual int getNParameters();

};
