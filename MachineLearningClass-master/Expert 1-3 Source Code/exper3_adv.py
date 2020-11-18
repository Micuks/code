#
# Weight Initialization
#
# To create this model, we're going to need to create a lot of weights and biases.
# One should generally initialize weights with a small amount of noise for symmetry
# breaking, and to prevent 0 gradients. Since we're using ReLU neurons, it is also
# good practice to initialize them with a slightly positive initial bias to avoid
# "dead neurons". Instead of doing this repeatedly while we build the model,
# let's create two handy functions to do it for us.
#
def weight_variable(shape):
  initial = tf.truncated_normal(shape, stddev=0.1)
  return tf.Variable(initial)

def bias_variable(shape):
  initial = tf.constant(0.1, shape=shape)
  return tf.Variable(initial)

#
# Convolution and Pooling
# 
# TensorFlow also gives us a lot of flexibility in convolution and pooling operations.
# How do we handle the boundaries? What is our stride size?
# In this example, we're always going to choose the vanilla version.
#
# Our convolutions use a stride of one and are zero padded so that the output is the 
# same size as the input.
#
# Our pooling is plain old max pooling over 2x2 blocks.
#
# We'll also abstract those operations into functions.
#
def conv2d(x, W):
  return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')

def max_pool_2x2(x):
  return tf.nn.max_pool(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')

#
# First Convolutional Layer
#
# Our first layer will consist of a convolution, followed by max pooling.
#
# The convolution will compute 32 features for each 5x5 patch.
# Its weight tensor will have a shape of [5, 5, 1, 32].
#
# The first two dimensions are the patch size (5)
# The next is the number of input channels (1)
# The last is the number of output channels (32)
#
# We will also have a bias vector with a component for each output channel.
#
W_conv1 = weight_variable([5, 5, 1, 32])
b_conv1 = bias_variable([32])

# To apply the layer, we first reshape x to a 4d tensor, with the second and third dimensions
# corresponding to image width and height, and the final dimension corresponding to the
# number of color channels.
x_image = tf.reshape(x, [-1, 28, 28, 1])

# We then convolve x_image with the weight tensor, add the bias, apply the ReLU function,
# and finally max pool.
# The max_pool_2x2 method will reduce the image size to 14x14.
h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1)
h_pool1 = max_pool_2x2(h_conv1)

#
# Second Convolutional Layer
#
# In order to build a deep network, we stack several layers of this type.
#
# The second layer will have 64 features for each 5x5 patch.
# The max_pool_2x2 method will reduce the image size to 7x7.
#
W_conv2 = weight_variable([5, 5, 32, 64])
b_conv2 = bias_variable([64])

h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)
h_pool2 = max_pool_2x2(h_conv2)

#
# Densely Connected Layer
#
# Now that the image size has been reduced to 7x7, we add a fully-connected layer
# with 1024 neurons to allow processing on the entire image.
#
# We reshape the tensor from the pooling layer into a batch of vectors,
# multiply by a weight matrix, add a bias, and apply a ReLU.
#
W_fc1 = weight_variable([7 * 7 * 64, 1024])
b_fc1 = bias_variable([1024])

h_pool2_flat = tf.reshape(h_pool2, [-1, 7*7*64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)

#
# Dropout
#
# To reduce overfitting, we will apply dropout before the readout layer.
# We create a placeholder for the probability that a neuron's output is kept during dropout.
# This allows us to turn dropout on during training, and turn it off during testing.
# TensorFlow's tf.nn.dropout op automatically handles scaling neuron outputs in addition
# to masking them, so dropout just works without any additional scaling.
#
keep_prob = tf.placeholder(tf.float32)
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)

#
# Readout Layer
#
# Finally, we add a layer, just like for the one layer softmax regression above.
#
W_fc2 = weight_variable([1024, 10])
b_fc2 = bias_variable([10])

y_conv = tf.matmul(h_fc1_drop, W_fc2) + b_fc2

#
# Train and evaluate
#
cross_entropy = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits_v2(labels=y_, logits=y_conv))

# We will replace the steepest gradient descent optimizer with the more sophisticated ADAM optimizer.
# We will add logging to every 100th iteration in the training process.
train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)
correct_prediction = tf.equal(tf.argmax(y_conv, 1), tf.argmax(y_, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

if False: # Don't execute for compiling blog    
   
    # We will also use tf.Session rather than tf.InteractiveSession.
    # This better separates the process of creating the graph (model sepecification)
    # and the process of evaluating the graph (model fitting).
    with tf.Session() as sess:
      sess.run(tf.global_variables_initializer())
      for i in range(2000):
        batch = mnist.train.next_batch(50)
        if i % 100 == 0:
          train_accuracy = accuracy.eval(feed_dict={x: batch[0], y_: batch[1], keep_prob: 1.0})
          print('step %d, training accuracy %g' % (i, train_accuracy))
        train_step.run(feed_dict={x: batch[0], y_: batch[1], keep_prob: 0.5})

      # Save the model --------------------------------------------
        
      # Build the signature_def_map.
      classification_inputs = tf.saved_model.utils.build_tensor_info(x)
      classification_outputs_classes = tf.saved_model.utils.build_tensor_info(y)
      classification_outputs_scores = tf.saved_model.utils.build_tensor_info(y_conv)

      classification_signature = (
        tf.saved_model.signature_def_utils.build_signature_def(
            inputs={tf.saved_model.signature_constants.CLASSIFY_INPUTS: classification_inputs},
            outputs={tf.saved_model.signature_constants.CLASSIFY_OUTPUT_CLASSES: classification_outputs_classes,
                tf.saved_model.signature_constants.CLASSIFY_OUTPUT_SCORES: classification_outputs_scores},
            method_name=tf.saved_model.signature_constants.CLASSIFY_METHOD_NAME))

      tensor_info_x = tf.saved_model.utils.build_tensor_info(x)
      tensor_info_y = tf.saved_model.utils.build_tensor_info(y)

      prediction_signature = (
          tf.saved_model.signature_def_utils.build_signature_def(
              inputs={'images': tensor_info_x},
              outputs={'scores': tensor_info_y},
              method_name=tf.saved_model.signature_constants.PREDICT_METHOD_NAME))

      export_path = './export_model'
      print('Exporting trained model to: %r' % export_path)
      builder = tf.saved_model.builder.SavedModelBuilder(export_path)
      builder.add_meta_graph_and_variables(
              sess, [tf.saved_model.tag_constants.SERVING],
              signature_def_map={
                   'predict_images':
                       prediction_signature,
                   tf.saved_model.signature_constants.DEFAULT_SERVING_SIGNATURE_DEF_KEY:
                       classification_signature,
              })
      builder.save()
   
      # Complete --------------------------------------------

      print('test accuracy %g' % accuracy.eval(feed_dict={x: mnist.test.images, y_: mnist.test.labels, keep_prob: 1.0}))