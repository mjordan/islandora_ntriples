#### Overview

A proof-of-concept module to allow loading and querying, via Drupal's autocomplete functionality, of Linked Data in N-Triples format. The best source of data in N-Triples is http://id.loc.gov/download/. 

#### Installation

Clone this module into your drupal modules folder and enable it.

After you enable the module, load an N-Triples file by running the following drush command:

```
drush load-islandora-ntriples /path/to/data.nt foo
```

where '/path/to/data.nt' is the path to the file containing N-Triples and 'foo' is an alias (string with no spaces or punctuation other than underscores) identifying the vocabulary that the triples are from. 'all' is a reserved alias; do not use it.

Two more commands you can run are:

```drush list-islandora-ntriples-vocabs```: Lists all distinct vocabularies in islandora_ntriples_triples table.

```drush purge-islandora-ntriples-vocab {alias}```: Purge all entries from islandora_ntriples_triples table with the specified vocab alias.

#### Testing

After you have loaded at least one vocabulary, go to the admin form for the module (admin/islandora/ntriples) and type something. You should see the autocomplete in action.

#### Configuration

Integration with Islandora add/update metadata forms is ongoing. Currently, assigning an "Autocomplete Path" value of "islandora_ntriples/autocomplete/all" to a text field (using the Islandora Form Builder, for example) will allow that field to use all of the entries in the local N-Triples database, or, alternatively, assigning a value of "islandora_ntriples/autocomplete/{alias}" (where {alias} is a single vocabulary alias) will limit entries to that vocabulary.

#### License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)

