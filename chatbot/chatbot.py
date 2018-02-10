import seq2seq_model 
import data_utils 
import tensorflow as tf

def train(): 
    #prepare dataset 
    enc_train, dec_train = data_utils.prepare_custom_data(gConfig['working_directory']) 
    
    train_set = read_data(enc_train, dec_train)
    
    with tf.Session(config = config) as sess: 
        model = create_model(sess, false)
        
        while True: 
            sess.run(model)
   
# This seq2seq function: we use embedding for input and attention.     
def seq2seq_f(encoder_inputs, decoder_inputs, do_decode): 
    return tf.seq2seq.embedding_attention_seq2seq(
        encoder_inputs, decoder_inputs, cell, 
        num_encoder_symbols = source_vocab_size, 
        num_decoder_symbols = target_vocab_size, 
        embedding_size = size, 
        output_projection = output_projection, 
        feed_previous = do_decode)
        
        
    
