<?php

/**
 * @file
 * This file is empty by default because the base theme chain (Alpha & Omega) provides
 * all the basic functionality. However, in case you wish to customize the output that Drupal
 * generates through Alpha & Omega this file is a good place to do so.
 * 
 * Alpha comes with a neat solution for keeping this file as clean as possible while the code
 * for your subtheme grows. Please read the README.txt in the /preprocess and /process subfolders
 * for more information on this topic.
 */
 
 function omega_nomad_preprocess_page(&$vars) {
  if (drupal_is_front_page()) {
    unset($vars['page']['content']['system_main']['default_message']); //will remove message "no front page content is created"
    drupal_set_title(''); //removes welcome message (page title)
  }
}