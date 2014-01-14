#### Overview

A proof-of-concept module to allow loading and querying, via Drupal's autocomplete functionality, of Linked Data in N-Triples format. The best source of data in N-Triples is http://id.loc.gov. 

#### Installation

Clone this module into your drupal modules folder and enable it.

After you enable the module, load an N-Triples file by running the following drush command:

```
drush load-islandora-ntriples /path/to/data.nt foo
```

where '/path/to/data.nt' is the path to the file containing N-Triples and 'foo' is an alias (string with no spaces or punctuation) identifying the vocabulary that the triples are from.

Two more commands you can run are:

```drush purge-islandora-ntriples-vocab {alias}```: Purge all entries from islandora_ntriples_triples table with the specified vocab alias.

```drush list-islandora-ntriples-vocabs```: Lists all distinct vocabularies in islandora_ntriples_triples table.

#### Testing

After you have loaded at least one vocabulary, go to the admin form for the module (admin/islandora/ntriples) and type something. You should see the autocomplete in action.

Further instructions on how to integrate this module into your site are coming as soon as I figure them out.

#### License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)

