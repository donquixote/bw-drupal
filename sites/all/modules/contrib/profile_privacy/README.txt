Provides options for users to over ride visibility of their own profile fields.

INSTALL
--------------------------------------------------------------------------------
 - Drupal 7 - admin/modules


CONFIGURATION
--------------------------------------------------------------------------------
- This module does not have a settings page or central configuration. All additional features are made to existing forms.

Administer Profile Fields:
- Edit a profile field you wish to have privacy control (admin/config/people/profile)
- An additional checkbox is added in the Visibility section "Allow user to override default visibility"
- Check this box, and the user will be able to make a public field private or vice-versa

Editing a Profile:
- For every field for which the user is allowed to over ride the visibility a new checkbox is added below that field, "Do not display *field name* publicly". The visibility setting set in the profile field configuration is used as the default (private fields are checked, public fields are unchecked).


CAVEATS
--------------------------------------------------------------------------------
- This module only adjusts fields displayed by the profile module.
- If a field is private by default and the user is allowed to over ride in their profile, the field will not be added in the correct position. It will be appended to the list of public fields.
